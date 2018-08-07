mergeInto(LibraryManager.library, {
    setClipboard: function(text){
        var textArea = document.createElement("textarea");

        //
        // *** This styling is an extra step which is likely not required. ***
        //
        // Why is it here? To ensure:
        // 1. the element is able to have focus and selection.
        // 2. if element was to flash render it has minimal visual impact.
        // 3. less flakyness with selection and copying which **might** occur if
        //    the textarea element is not visible.
        //
        // The likelihood is the element won't even render, not even a flash,
        // so some of these are just precautions. However in IE the element
        // is visible whilst the popup box asking the user for permission for
        // the web page to copy to the clipboard.
        //

        // Place in top-left corner of screen regardless of scroll position.
        textArea.style.position = 'fixed';
        textArea.style.top = 0;
        textArea.style.left = 0;

        // Ensure it has a small width and height. Setting to 1px / 1em
        // doesn't work as this gives a negative w/h on some browsers.
        textArea.style.width = '2em';
        textArea.style.height = '2em';

        // We don't need padding, reducing the size if it does flash render.
        textArea.style.padding = 0;

        // Clean up any borders.
        textArea.style.border = 'none';
        textArea.style.outline = 'none';
        textArea.style.boxShadow = 'none';

        // Avoid flash of white box if rendered for any reason.
        textArea.style.background = 'transparent';


        textArea.value = text;

        document.body.appendChild(textArea);

        textArea.select();

        try {
            var successful = document.execCommand('copy');
            if(!successful)
            console.log("Couldn't copy text");
        } catch (err) {
            console.log('There was an error while copying the text');
        }

        document.body.removeChild(textArea);
    },
    setCookie: function(p_name, p_value){
        var name = Pointer_stringify(p_name);
        var value = Pointer_stringify(p_value);
        var date = new Date();
        date.setTime(date.getTime() + (365*24*60*60*1000));
        document.cookie = name + "=" + value + "; expires=" + date.toUTCString();
    },
    getCookie: function(p_name){
        var name = Pointer_stringify(p_name);
        var ca = document.cookie.split(";");
        for(var i=0; i<ca.length; i++){
            var c = ca[i];
            while (c.charAt(0)==' ')
                c = c.substring(1);
            if (c.indexOf(name+"=") == 0){
			    var value = c.substring(name.length+1,c.length);
                return allocate(intArrayFromString(value), 'i8', ALLOC_NORMAL);
            }
        }
        return null;
    },
    js_show_menu: function(){
        var menu = document.getElementById('menu');
        menu.style.display = "block";
    },
    js_hide_menu: function(){
        var menu = document.getElementById('menu');
        menu.style.display = "none";
    }
});