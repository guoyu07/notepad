var cgiPath = "cgi-bin/notes.cgi";
var create=0, get=1, put=2, del=3;
var notes = {
  0:{
      "noteId" : -1,
      "noteTitle" : "dummy1",
      "noteBody" : "dummy11",
      "lastModifiedOn" : "never1"
  },
    1:{
        "noteId" : -2,
        "noteTitle" : "dummy2",
        "noteBody" : "dummy21",
        "lastModifiedOn" : "never2"
    }
};

checkCookie();



$('#login').on('click',function () {
    var userName, password;
    userName = $('#username').val();
    password = $('#password').val();
    if(userName == "" || userName == null){
//TODO has-warning
    }else if(password == "" || password == null){
//TODO has-warning
    }else{
        $('#password').val("************************");
        authenticate(userName,password);
    }
});

//authenticate and set cookie
function authenticate(userName, password){
    var xhttp = new XMLHttpRequest();
    var outJson = {};
    outJson.identifier = "a";
    outJson.userName = userName;
    outJson.password = password;

    xhttp.open("POST", cgiPath, true);
    xhttp.send(JSON.stringify(outJson));
    outJson = {}; password = "";

    xhttp.onreadystatechange = function () {
      if(this.readyState == 4 && this.status == 200){
          var inJson = JSON.parse(this.responseText);
          var areValid = Boolean(inJson.areValid);

          if(areValid){
              setCookie("uid",userName,1);
              checkCookie();
          }else{
              //throw error
          }
      }
    };
}

//check cookie

//******//Assume user is authenticated
var userName;
/*
* Get all notes list (titles)
* should have note Id, title, body, last modified, etc.
* */
function getNotes() {
    var xhttp = new XMLHttpRequest();
    var outJson = {};
    outJson.identifier = "g";
    outJson.userName = userName;

    xhttp.open("POST", cgiPath, true);
    xhttp.send(JSON.stringify(outJson));

    xhttp.onreadystatechange = function () {
        if(this.readyState == 4 && this.status == 200){
            var inJson = JSON.parse(this.responseText);
            notes = inJson.notes;
            updateNotesDisplay();

        }
    };

}

function updateNotesDisplay() {
    $('#notesContainer').find('a')
        .remove()
        .end();
    for(var i=0; i=notes.length; i++){
        $('#notesContainer').find('a').append('<a href ="#"  class="list-group-item list-group-item-action" onClick="displayNoteModal('+i+');">'+notes[i].noteTitle+'</a>')
    }

}

function displayNoteModal(noteIndex){

    $("#noteTitle").val(notes[noteIndex].noteTitle);
    $("#noteBody").val(notes[noteIndex].noteBody);

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
        $("#updateNote").on('click', createHandler);
    }else{              //update or delete
        $("#updateNote").on('click', updateHandler);
        $("#deleteNote").on('click', deleteHandler);
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
        case create: outJson.identifier = "c"; break;
        case get:    outJson.identifier = "g"; break;
        case put:    outJson.identifier = "p"; break;
        case del:    outJson.identifier = "d"; break;
    }
    outJson.note.noteId = noteIndex;
    outJson.note.noteTitle = nTitle;
    outJson.note.noteBody  = nBody;

    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", cgiPath, true);
    xhttp.send(JSON.stringify(outJson));

    xhttp.onreadystatechange = function () {
        if(this.readyState == 4 && this.status == 200) {
            var inJson = JSON.parse(this.responseText);
            if(Boolean(inJson.success))
                console.log("update successful");
            else
                console.log("update failed");
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
setCookie("uid",userName,-1);
checkCookie();






























/******************#myModal*****************/
function centerModal() {
    $(this).css('display', 'block');
    var $dialog = $(this).find(".modal-dialog");
    var offset = ($(window).height() - $dialog.height()) / 2;
    // Center modal vertically in window
    $dialog.css("margin-top", offset);
}


var titleData = "I am title two";
$('.modal').on('show.bs.modal', centerModal);


$(window).on("resize", function () {
    $('.modal:visible').each(centerModal);
});

// $("#saveChanges").on('click', handler);










/******************Cookies*****************/
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
    var user = getCookie("username");
    if (user != "") {
       // user = prompt("Please enter your name:", "");
        alert("Welcome again " + user);
        window.location = '/';
    } else {
        window.location = 'login.html';
        // if (user != "" && user != null) {
        //     setCookie("username", user, 1);
        // }
    }
}

