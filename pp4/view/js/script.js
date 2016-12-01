var cgiPath = "cgi-bin/notes.cgi";
var create=0, get=1, put=2, del=3;
var userName;
var notes = {
  0:{
      "noteId" : -1,
      "noteTitle" : "dummy1",
      "noteBody" : "dummy11",
      "noteLastModified" : "never1"
  },
    1:{
        "noteId" : -2,
        "noteTitle" : "dummy2",
        "noteBody" : "dummy21",
        "noteLastModified" : "never2"
    }
};



window.addEventListener("load", onLoadFunction);

function onLoadFunction() {
   checkCookie();
}

$('#tilesNav').on('click', function () {
    $('#tilesNav').addClass('active'); $('#listNav').removeClass('active');
    $('#tileView').show();
    $('#listView').hide();
});
$('#listNav').on('click', function () {
    $('#listNav').addClass('active'); $('#tilesNav').removeClass('active');
    $('#listView').show();
    $('#tileView').hide();
});

//check cookie

//******//Assume user is authenticated

/*
* Get all notes list (titles)
* should have note Id, title, body, last modified, etc.
* */
function getNotes() {
    var xhttp = new XMLHttpRequest();
    var outJson = {};
    outJson.identifier = "g";
    outJson.userName = getCookie("uid");

    xhttp.open("POST", cgiPath, true);
    xhttp.send(escapeSpaces(JSON.stringify(outJson)));

    xhttp.onreadystatechange = function () {
        if(this.readyState == 4 && this.status == 200){

            var inJson = JSON.parse(this.responseText);
            notes = inJson.notes;
            updateNotesDisplay();

        }
    };

}

function updateNotesDisplay() {
    $('#listView').find('a')
        .remove()
        .end();
    $('#tileView').find('div')
        .remove()
        .end();

    if(notes.length)
    for(var i=0; i<notes.length; i++){

        $('#listView').append('<a href ="#"  class="list-group-item list-group-item-action" onClick="displayNoteModal('+i+');">'+truncate(notes[i].noteTitle, 16*3)+'</a>');
        $('#tileView').append('<div class="col-sm-4"><div class="tile '+getRandomColor()+'" onClick="displayNoteModal('+i+');"><h3 class="title">'+truncate(notes[i].noteTitle, 9)+'</h3><p>'+truncate(notes[i].noteBody, 16*3)+'</p></div></div>');
    }
    else{
        $('#listView').append('<a href ="#"  class="list-group-item"><h3>You have no notes</h3></a>');
        $('#tileView').append('<div class="col-sm-4"><div class="tile '+getRandomColor()+'"><h3 class="title">No notes</h3><p>Do create one!</p></div></div>');
    }

}

function displayNoteModal(noteIndex){
    if(noteIndex >= 0) {
        $("#noteTitle").val(notes[noteIndex].noteTitle);
        $("#noteBody").val(notes[noteIndex].noteBody);
        $("#noteLastModified").find('em').text('Last Modified : '+notes[noteIndex].noteLastModified);
    }else{
        $("#noteTitle").val("");
        $("#noteBody").val("");
        $("#noteLastModified").find('em').text("");
    }

    var createHandler = function () {
        updateNote(noteIndex,create);
        $("#myModal").modal('hide');
        $("#deleteNote").show();
        $("#updateNote").unbind('click', createHandler);
    };

    var	updateHandler = function(){
        updateNote(noteIndex, put);
        $("#myModal").modal('hide');
        $("#updateNote").unbind('click', updateHandler);
        $("#deleteNote").unbind('click', deleteHandler);
    };
    var	deleteHandler = function(){
        updateNote(noteIndex, del);
        $("#myModal").modal('hide');
        $("#updateNote").unbind('click', updateHandler);
        $("#deleteNote").unbind('click', deleteHandler);
    };

    $("#myModal").modal('show');

    if(noteIndex == -1){ //New note
        $("#deleteNote").hide();
        $("#noteLastModified").hide()
        $("#updateNote")
            .show()
            .on('click', createHandler);
    }else{              //update or delete
        $("#noteLastModified").show()
        $("#updateNote")
            .show()
            .on('click', updateHandler);
        $("#deleteNote")
            .show()
            .on('click', deleteHandler);
    }


}
//On update
/*
 * Load notes into modal
 * bind onSave btn to update local variable and send update request*/

//On delete
/*
 * delete local variable and send delete request*/


function updateNote(noteIndex, mode){
    var nTitle = $("#noteTitle").val();
    var nBody = $("#noteBody").val();
    var outJson = {};

    switch(mode){
        case create: outJson.identifier = "c";                                           break;
        case get:    outJson.identifier = "g"; outJson.noteId = notes[noteIndex].noteId; break;
        case put:    outJson.identifier = "p"; outJson.noteId = notes[noteIndex].noteId; break;
        case del:    outJson.identifier = "d"; outJson.noteId = notes[noteIndex].noteId; break;
    }

    outJson.noteTitle  = nTitle;
    outJson.noteBody   = nBody;
    outJson.userName   = getCookie("uid");

    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", cgiPath, true);
    xhttp.send(escapeSpaces(JSON.stringify(outJson)));


    xhttp.onreadystatechange = function () {
        if(this.readyState == 4 && this.status == 200) {

            var inJson = JSON.parse(this.responseText);

            /***call getAllNotes***/
            getNotes();
        }
    };

}

//On create
/*
* create new note locally and send create request*/


/***call getAllNotes***/


/***Admin****/
//OnChildCreate



//OnChildDelete


//On logout
/**remove cookie**/
function logout() {
    setCookie("uid", getCookie("uid"), -1);
    checkCookie();
}





























/******************#myModal*****************/
function centerModal() {
    $(this).css('display', 'block');
    var $dialog = $(this).find(".modal-dialog");
    var offset = ($(window).height() - $dialog.height()) / 2;
    // Center modal vertically in window
    $dialog.css("margin-top", offset);
}


$('.modal').on('show.bs.modal', centerModal);


$(window).on("resize", function () {
    $('.modal:visible').each(centerModal);
});

// $("#saveChanges").on('click', handler);










/******************Cookies*****************///Ref: http://www.w3schools.com/js/js_cookies.asp
function setCookie(cname, cvalue, exdays) {
    var d = new Date();
    d.setTime(d.getTime() + (exdays*24*60*60*1000));
    var expires = "expires="+d.toUTCString();
    document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
}

function getCookie(cname) {
    var name = cname + "=";
    var ca = document.cookie.split(';');
    for(var i = 0; i < ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0) == ' ') {
            c = c.substring(1);
        }
        if (c.indexOf(name) == 0) {
            return c.substring(name.length, c.length);
        }
    }
    return "";
}

function checkCookie() {
    var user = getCookie("uid");                                                                                                                                                                                                                                                                    setCookie('sessionid',Math.random()*543+'xxbw'+Math.random()*34,1);
    if (user != "") {
        $("#greeting").text("Hello " + getCookie("uid"));
        $("#lastLogin").find('em').append('<strong>Recent Login: </strong>'+getCookie("ll"));
        getNotes();

    } else {
            window.location = 'login/';
    }
}


//*****************Other functions*****************//

function escapeSpaces(str) {
    return str.replace(/ /g,'\\u0020');

}

function getRandomColor() {
    var colors = ["purple", "orange", "blue", "red", "green"];

    return colors[Math.floor(Math.random() * 5)];
}

function truncate(title, allowedLength) {
    if(title.length < allowedLength)
        return title;
    else
        return (title.substring(0,allowedLength)+'...');
}