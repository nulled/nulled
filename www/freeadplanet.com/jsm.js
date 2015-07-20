var jsm = {
  DEBUG: 0,
  byId: function(id) {
    return document.getElementById(id);
  }
}

jsm.ajax = {

  connection: null,

  create: function() {
    try { return new XMLHttpRequest(); } catch (e) {}
    try { return new ActiveXObject("Msxml3.XMLHTTP"); } catch (e) {}
    try { return new ActiveXObject("Msxml2.XMLHTTP"); } catch (e) {}
    try { return new ActiveXObject("Microsoft.XMLHTTP"); } catch (e) {}
    //alert("XMLHttpRequest not supported.");
    return null;
  },

  get: function(url, handler) {
    if (! handler) handler = null;
    jsm.ajax.connection = jsm.ajax.create();
    if (jsm.ajax.connection == null) return;
    jsm.ajax.connection.onreadystatechange = handler;
    jsm.ajax.connection.open("GET", url, true);
    jsm.ajax.connection.send(null);
  }
}

jsm.handler = {};

// In DOM-compliant browsers, our functions are trivial wrappers around
// addEventListener() and removeEventListener().
if (document.addEventListener) {
  jsm.handler.add = function(element, eventType, handler) {
    element.addEventListener(eventType, handler, false);
  };

  jsm.handler.remove = function(element, eventType, handler) {
    element.removeEventListener(eventType, handler, false);
  };
}
// In IE 5 and later, we use attachEvent() and detachEvent(), with a number of
// hacks to make them compatible with addEventListener and removeEventListener.
else if (document.attachEvent) {
  jsm.handler.add = function(element, eventType, handler) {
    if (jsm.handler._find(element, eventType, handler) != -1) return;

    var wrappedHandler = function(e) {
      if (! e) e = window.event;

      // Create a synthetic event object with partial compatibility
      // with DOM events.
      var event = {
        _event: e,
        type: e.type,
        target: e.srcElement,
        currentTarget: element,
        relatedTarget: e.fromElement?e.fromElement:e.toElement,
        eventPhase: (e.srcElement==element)?2:3,

        // Mouse coordinates
        clientX: e.clientX, clientY: e.clientY,
        screenX: e.screenX, screenY: e.screenY,

        // Key state
        altKey: e.altKey, ctrlKey: e.ctrlKey,
        shiftKey: e.shiftKey, charCode: e.keyCode,

        stopPropagation: function() { this._event.cancelBubble = true; },
        preventDefault: function() { this._event.returnValue = false; }
      }

      if (Function.prototype.call)
        handler.call(element, event);
      else {
        element._currentHandler = handler;
        element._currentHandler(event);
        element._currentHandler = null;
      }
    };

    element.attachEvent("on" + eventType, wrappedHandler);

    var h = {
      element: element,
      eventType: eventType,
      handler: handler,
      wrappedHandler: wrappedHandler
    };

    var d = element.document || element;
    var w = d.parentWindow;

    var id = jsm.handler._uid();
    if (! w._allHandlers) w._allHandlers = {};
    w._allHandlers[id] = h;

    if (! element._handlers) element._handlers = [];
    element._handlers.push(id);

    if (! w._onunloadHandlerRegistered) {
      w._onunloadHandlerRegistered = true;
      w.attachEvent("onunload", jsm.handler._removeAllHandlers);
    }
  };

  jsm.handler.remove = function(element, eventType, handler) {
    var i = jsm.handler._find(element, eventType, handler);
    if (i == -1) return;

    var d = element.document || element;
    var w = d.parentWindow;

    var handlerId = element._handlers[i];

    var h = w._allHandlers[handlerId];
    element.detachEvent("on" + eventType, h.wrappedHandler);
    element._handlers.splice(i, 1);
    delete w._allHandlers[handlerId];
  };

  // A utility function to find a handler in the element._handlers array
  // Returns an array index or -1 if no matching handler is found
  jsm.handler._find = function(element, eventType, handler) {
    var handlers = element._handlers;
    if (! handlers) return -1;

    var d = element.document || element;
    var w = d.parentWindow;

    for (var i = handlers.length-1; i >= 0; i--) {
      var handlerId = handlers[i];
      var h = w._allHandlers[handlerId];
      if (h.eventType == eventType && h.handler == handler)
        return i;
    }
    return -1;
  };

  // This function is registered as the onunload handler with
  // attachEvent.  This means that the this keyword refers to the
  // window in which the event occurred.
  jsm.handler._removeAllHandlers = function() {
    var w = this;

    for (id in w._allHandlers) {
      var h = w._allHandlers[id];
      h.element.detachEvent("on" + h.eventType, h.wrappedHandler);
      delete w._allHandlers[id];
    }
  }

  // Private utility to generate unique handler ids
  jsm.handler._counter = 0;
  jsm.handler._uid = function() { return "h" + jsm.handler._counter++; };
}
