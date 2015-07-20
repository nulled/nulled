<?php
/**
* Validate an Email Address Via SMTP
* This queries the SMTP server to see if the email address is accepted.
* @copyright http://creativecommons.org/licenses/by/2.0/ - Please keep this comment intact
*/
class SMTP_validateEmail
{
  public $sock;
  public $user;
  public $domain;
  public $port = 25;
  public $max_conn_time = 30;
  public $max_read_time = 5;
  public $from_user = 'user';
  public $from_domain = 'localhost';
  public $debug = false;

  function __construct($email = false, $sender = false)
  {
    if ($email)
    {
      $this->setEmail($email);
    }

    if ($sender)
    {
      $this->setSenderEmail($sender);
    }
  }

  function setEmail($email)
  {
    list($user, $domain) = explode('@', $email);

    $this->user   = $user;
    $this->domain = $domain;
  }

  function setSenderEmail($email)
  {
    list($user, $domain) = explode('@', $email);

    $this->from_user = $user;
    $this->from_domain = $domain;
  }

  /**
  * Validate an Email Address
  * @param String $email Email to validate (recipient email)
  * @param String $sender Senders Email
  */
  function validate($email = false, $sender = false)
  {
    if ($email)
    {
      $this->setEmail($email);
    }

    if ($sender)
    {
      $this->setSenderEmail($sender);
    }

    // retrieve SMTP Server via MX query on domain
    $result = getmxrr($this->domain, $hosts, $mxweights);

    // retrieve MX priorities
    for($n=0; $n < count($hosts); $n++)
    {
      $mxs[$hosts[$n]] = $mxweights[$n];
    }

    asort($mxs);
    // last fallback is the original domain
    array_push($mxs, $this->domain);

    $this->debug(print_r($mxs, 1));

    $timeout = $this->max_conn_time/count($hosts);
    // try each host
    while(list($host) = each($mxs))
    {
      // connect to SMTP server
      $this->debug("try $host:$this->port\n");

      if ($this->sock = fsockopen($host, $this->port, $errno, $errstr, (float) $timeout))
      {
        stream_set_timeout($this->sock, $this->max_read_time);
        break;
      }
    }

    // did we get a TCP socket
    if ($this->sock)
    {
      $reply = fread($this->sock, 2082);
      preg_match('/^([0-9]{3}) /ims', $reply, $matches);
      $code = isset($matches[1]) ? $matches[1] : '';

      if($code != '220')
      {
        // MTA gave an error...
        return false;
      }

      // say helo
      $this->send("HELO ".$this->from_domain);
      // tell of sender
      $this->send("MAIL FROM: <".$this->from_user.'@'.$this->from_domain.">");
      // ask of recepient
      $reply = $this->send("RCPT TO: <".$this->user.'@'.$this->domain.">");
      // quit
      $this->send("quit");
      // close socket
      fclose($this->sock);
      // get code and msg from response
      preg_match('/^([0-9]{3}) /ims', $reply, $matches);

      $code = isset($matches[1]) ? $matches[1] : '';

      if ($code == '250')
      {
        // you received 250 so the email address was accepted
        return true;
      }
      else if ($code == '451' OR $code == '452')
      {
        // you received 451 so the email address was greylisted (or some temporary error occured on the MTA) - so assume is ok
        return true;
      }
    }
    return false;
  }

  function send($msg)
  {
    fwrite($this->sock, $msg."\r\n");

    $reply = fread($this->sock, 2082);

    $this->debug(">>>\n$msg\n");
    $this->debug("<<<\n$reply");

    return $reply;
  }

  /**
  * Simple function to replicate PHP 5 behaviour. http://php.net/microtime
  */
  function microtime_float()
  {
    list($usec, $sec) = explode(" ", microtime());
    return ((float)$usec + (float)$sec);
  }

  function debug($str)
  {
    if ($this->debug)
    {
      echo $str;
    }
  }

};

?>