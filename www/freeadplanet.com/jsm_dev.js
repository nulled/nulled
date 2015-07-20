/*
A simple Javascript Library I wrote as a learning experience as well as
avoiding the overly bloated Javascript libraries out there which I will
not mention by name.

Licensed under GPLv2
Matt Kukowski - elitescripts2000 [AT] yahoo [DOT] com - 2007

Currently it supports the following capabilities (modules):
- dnd : Make any element Drag n Droppable
- ajax : Ajax made easy.
- menu : Create dropdown menus and even animate the drop stage
- tooltip : Attach a popup with content (tips) about a tool
- handler : A cross browser (IE/FF) universal way of attaching Event Handlers

This library tries to seperate Structure and Presentation from Javascript
behavior the best it can. In modules like the menu module this library
expects certain html structure. ( Such as using div tags nested a certain
way to create a drop down menu list. ) The styling of the menu is minimized,
such as only creating a thin black borders. The rest should be stylized with
CSS and content created with html again such as div tags. Where stylizing does
take place in the javascript it will be passed in to the js function. In this
manner it tries to seperate the Styles so you can style them with CSS instead.
*/

/*
// functions to use in the future
function setOpacity(value) {
	testObj.style.opacity = value/10;
	testObj.style.filter = 'alpha(opacity=' + value*10 + ')';
}

// below is CSS, HTML then JS which will style <input type=file>
// http://www.quirksmode.org/dom/inputfile.html
div.fileinputs {
	position: relative;
}
input.file {
	position: relative;
	text-align: right;
	-moz-opacity:0 ;
	filter:alpha(opacity: 0);
	opacity: 0;
	z-index: 2;
}
<div class="fileinputs">
	<input type="file" class="file">
</div>
var W3CDOM = (document.createElement && document.getElementsByTagName);
function initFileUploads() {
	if (!W3CDOM) return;
	var fakeFileUpload = document.createElement('div');
	fakeFileUpload.className = 'fakefile';
	fakeFileUpload.appendChild(document.createElement('input'));
	var image = document.createElement('img');
	image.src='pix/button_select.gif';
	fakeFileUpload.appendChild(image);
	var x = document.getElementsByTagName('input');
	for (var i=0;i<x.length;i++) {
		if (x[i].type != 'file') continue;
		if (x[i].parentNode.className != 'fileinputs') continue;
		x[i].className = 'file hidden';
		var clone = fakeFileUpload.cloneNode(true);
		x[i].parentNode.appendChild(clone);
		x[i].relatedElement = clone.getElementsByTagName('input')[0];
		x[i].onchange = x[i].onmouseout = function () {
			this.relatedElement.value = this.value;
		}
	}
}

// getting styles, width etc is tricky this function is the best at present.
// http://www.quirksmode.org/dom/getstyles.html
function getStyle(el,styleProp)
{
	var x = document.getElementById(el);
	if (x.currentStyle)
		var y = x.currentStyle[styleProp];
	else if (window.getComputedStyle)
		var y = document.defaultView.getComputedStyle(x,null).getPropertyValue(styleProp);
	return y;
}
*/


var jsm = {
  DEBUG: 0,
  byId: function(id) {
    return document.getElementById(id);
  }
}

jsm.dnd = {

  dragObject: [],
  mouseOffset: null,
  dragObjCurrent: null,

  makeDraggable: function(item) {
    if (! item.id) return;

    jsm.handler.add(document, 'mousemove', jsm.dnd.mouseMove);

    jsm.handler.add(item, 'mouseup', function(e) {
      //item.style.overflow = 'auto';
      jsm.dnd.dragObject[item.id] = null;
      jsm.dnd.dragObjCurrent = null;
      if (e.stopPropagation) e.stopPropagation();
    });

    jsm.handler.add(item, 'mousedown', function(e) {
      jsm.dnd.dragObjCurrent = item.id;
      jsm.dnd.dragObject[item.id] = this;
      jsm.dnd.dragObject[item.id].style.position = 'absolute';
      //jsm.dnd.dragObject[item.id].style.overflow = 'hidden';
      jsm.dnd.mouseOffset = jsm.dnd.getMouseOffset(this, e);
      if (e.stopPropagation) e.stopPropagation();
    });
  },

  mouseMove: function(e) {
    if (jsm.dnd.dragObject[jsm.dnd.dragObjCurrent]) {
      var mousePos = jsm.dnd.getMouseCoords(e);
      jsm.dnd.dragObject[jsm.dnd.dragObjCurrent].style.top  = (mousePos.y - jsm.dnd.mouseOffset.y) + 'px';
      jsm.dnd.dragObject[jsm.dnd.dragObjCurrent].style.left = (mousePos.x - jsm.dnd.mouseOffset.x) + 'px';
    }
  },

  getPosition: function(e) {
  	var left = 0;
  	var top = 0;

		while (e.offsetParent) {
			left += e.offsetLeft;
			top  += e.offsetTop;
			e = e.offsetParent;
		}

		left += e.offsetLeft;
		top  += e.offsetTop;

  	return {
  	  x: left,
  	  y: top
  	};
  },

  getMouseCoords: function(e) {
    if (e.pageX || e.pageY) {
      return {
        x: e.pageX,
        y: e.pageY
      };
    }
    return {
      x: e.clientX + document.body.scrollLeft - document.body.clientLeft,
      y: e.clientY + document.body.scrollTop  - document.body.clientTop
    };
  },

  getMouseOffset: function(target, e) {
    var docPos   = jsm.dnd.getPosition(target);
    var mousePos = jsm.dnd.getMouseCoords(e);
    return {x: mousePos.x - docPos.x,
            y: mousePos.y - docPos.y};
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

jsm.menu = {

  delayTimeout: 1000,
  tablistIDs: [],
  tabListTimeout: null,
  id: null,
  tabListHeights: [],
  animate: [],
  animationInterval: null,
  fadeInterval: null,
  currentHeight: 0,
  currentOpacity: 100,

  setTab: function(tab, tablist, colors, animate) {
    if (! tab.id) return;
    if (! tablist.id) return;

    jsm.menu.tablistIDs[jsm.menu.tablistIDs.length] = tablist.id;

    jsm.menu.animate[tablist.id] = animate;

    tablist.style.display = 'block';
    jsm.menu.tabListHeights[tablist.id] = tablist.offsetHeight + 1;
    tablist.style.display = 'none';

    tablist.style.position = 'absolute';

    var divs = tablist.getElementsByTagName('div');

    for (var i=0; i < divs.length; i++) {

      divs[i].style.border = '0px solid black';

      if (i+1 < divs.length) { // skip last link
        divs[i].style.borderBottom = '1px solid black';
      }

      jsm.handler.add(divs[i], 'mouseover', function(e) {
        this.style.backgroundColor = colors[3];
        if (jsm.menu.tabListTimeout) {
          clearTimeout(jsm.menu.tabListTimeout);
        }
        tab.style.backgroundColor = colors[1];
        jsm.menu.id = tablist.id;
        jsm.menu.hideMenus(jsm.menu.id);
        if (e.stopPropagation) e.stopPropagation();
      });

      jsm.handler.add(divs[i], 'mouseout', function(e) {
        this.style.backgroundColor = colors[2];
        jsm.menu.id = tablist.id;
        jsm.menu.tabListTimeout = setTimeout("jsm.menu.hideMenu(jsm.menu.id)", jsm.menu.delayTimeout);
        tab.style.backgroundColor = colors[0];
        if (e.stopPropagation) e.stopPropagation();
      });
    }

    jsm.handler.add(tab.firstChild, 'mouseover', function(e) {
      tablist.style.display = 'none';
      if (jsm.menu.tabListTimeout) {
        clearTimeout(jsm.menu.tabListTimeout);
      }
      if (jsm.menu.fadeInterval) {
        clearInterval(jsm.menu.fadeInterval);
      }
      tab.style.backgroundColor = colors[1];
      jsm.menu.id = tablist.id;
      jsm.menu.hideMenus(jsm.menu.id);
      if (jsm.menu.animate[tablist.id]) {
        //jsm.menu.animateMenuDown(jsm.menu.id);
        jsm.dnd.currentOpacity = 0;
        tablist.style.opacity = 0;
  	    tablist.style.filter = 'alpha(opacity=0)';
        tablist.style.display = 'block';
        jsm.menu.fadeInterval = setInterval("jsm.menu.fadeInMenuInterval(jsm.menu.id)", 50);

      } else {
        tablist.style.display = 'block';
      }
      if (e.stopPropagation) e.stopPropagation();
    });

    jsm.handler.add(tab.firstChild, 'mouseout', function(e) {
      // place the tabcontent under the tab
      // if tab is made draggable to recalculate position
      var pos = jsm.dnd.getPosition(tab);
      pos.y += tab.offsetHeight;
      tablist.style.top  = pos.y + 'px';
      tablist.style.left = pos.x + 'px';
      jsm.menu.id = tablist.id;
      if (jsm.menu.animate[tablist.id]) {
        jsm.menu.fadeInterval = setInterval("jsm.menu.fadeOutMenuInterval(jsm.menu.id)", 50);
      } else {
        jsm.menu.tabListTimeout = setTimeout("jsm.menu.hideMenu(jsm.menu.id)", jsm.menu.delayTimeout);
      }
      tab.style.backgroundColor = colors[0];
      if (e.stopPropagation) e.stopPropagation();
    });

    // place the tabcontent under the tab
    var pos = jsm.dnd.getPosition(tab);
    pos.y += tab.offsetHeight;
    tablist.style.top  = pos.y + 'px';
    tablist.style.left = pos.x + 'px';
  },

  hideMenu: function(itemID) {
    jsm.byId(itemID).style.display = 'none';
  },

  hideMenus: function(itemID) {
    for (var i=0; i < jsm.menu.tablistIDs.length; i++) {
      var id = jsm.menu.tablistIDs[i];
      if (id != itemID) {
        //document.getElementById(id).style.display = 'none';
        jsm.byId(id).style.display = 'none';
      }
    }
  },

  animateMenuDown: function(itemID) {
    if (jsm.menu.animationInterval) {
      clearInterval(jsm.menu.animationInterval);
    }
    var el = document.getElementById(itemID);
    el.style.overflow = 'hidden';
    el.style.height = '0px';
    jsm.menu.currentHeight = 0;
    jsm.menu.id = itemID;
    jsm.menu.animationInterval = self.setInterval("jsm.menu.animateMenuDownInterval(jsm.menu.id)", 25);
  },

  animateMenuDownInterval: function(itemID) {
    var el = document.getElementById(itemID);
    el.style.display = 'block';
    jsm.menu.currentHeight += 10;
    if (jsm.menu.currentHeight >= jsm.menu.tabListHeights[itemID]) {
      clearInterval(jsm.menu.animationInterval);
      el.style.height = jsm.menu.tabListHeights[itemID] + 'px';
    } else {
      el.style.height = jsm.menu.currentHeight + 'px';
    }
  },

  fadeInMenuInterval: function(itemID) {
    var el = document.getElementById(itemID);
    jsm.dnd.currentOpacity += .25;
    if (jsm.dnd.currentOpacity >= 10) {
      clearInterval(jsm.menu.fadeInterval);
      el.style.opacity = 1;
  	  el.style.filter = 'alpha(opacity=100)';
    } else {
    	el.style.opacity = jsm.dnd.currentOpacity / 10;
    	el.style.filter = 'alpha(opacity=' + jsm.dnd.currentOpacity * 10 + ')';
    }
  },

  fadeOutMenuInterval: function(itemID) {
    var el = document.getElementById(itemID);
    jsm.dnd.currentOpacity -= .25;
    if (jsm.dnd.currentOpacity <= 0) {
      clearInterval(jsm.menu.fadeInterval);
      el.style.opacity = 0;
  	  el.style.filter = 'alpha(opacity=0)';
    } else {
    	el.style.opacity = jsm.dnd.currentOpacity / 10;
    	el.style.filter = 'alpha(opacity=' + jsm.dnd.currentOpacity * 10 + ')';
    }
  }
}

jsm.tooltip = {

  delayTimeout: 1000,
  id: [],
  timeoutHandle: [],

  create: function(tool, tip) {
    if (! tip.id) return;

    tool.style.position = 'absolute';

    tip.style.position = 'absolute';
    tip.style.display = 'none';

    var pos = jsm.dnd.getPosition(tool);
    pos.y += tool.offsetHeight;
    tip.style.top  = pos.y + 'px';
    tip.style.left = pos.x + 'px';

    jsm.handler.add(tool, 'mouseover', function(e) {
      clearTimeout(jsm.tooltip.timeoutHandle[tip.id]);
      delete jsm.tooltip.id[tip.id];
      tip.style.display = 'block';
      // readjust if tool is draggable
      var pos = jsm.dnd.getPosition(tool);
      pos.y += tool.offsetHeight;
      tip.style.top  = pos.y + 'px';
      tip.style.left = pos.x + 'px';
      if (e.stopPropagation) e.stopPropagation();
    });

    jsm.handler.add(tool, 'mouseout', function(e) {
      jsm.tooltip.id[tip.id] = tip.id;
      jsm.tooltip.timeoutHandle[tip.id] = setTimeout("jsm.tooltip.hideTip()", jsm.tooltip.delayTimeout);
      if (e.stopPropagation) e.stopPropagation();
    });

    jsm.handler.add(tip, 'mouseover', function(e) {
      clearTimeout(jsm.tooltip.timeoutHandle[tip.id]);
      delete jsm.tooltip.id[tip.id];
      if (e.stopPropagation) e.stopPropagation();
    });

    jsm.handler.add(tip, 'mouseout', function(e) {
      jsm.tooltip.id[tip.id] = tip.id;
      jsm.tooltip.timeoutHandle[tip.id] = setTimeout("jsm.tooltip.hideTip()", jsm.tooltip.delayTimeout);
      if (e.stopPropagation) e.stopPropagation();
    });
  },

  hideTip: function() {
    for (var keyvar in jsm.tooltip.id) {
      var el = document.getElementById(jsm.tooltip.id[keyvar]);
      if (el) {
        delete jsm.tooltip.id[keyvar];
        el.style.display = 'none';
        if (jsm.DEBUG) {
          document.getElementById('debug').innerHTML += 'hideTip(): '  + '<br />';
        }
      }
    }
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