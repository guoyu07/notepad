var cgiPath = "cgi-bin/notes.cgi";

var notes = {
  0:{
      "noteId" : -1,
      "noteTitle" : "",
      "noteBody" : "",
      "lastModifiedOn" : ""
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

/*
* Get all notes list (titles)
* should have note Id, title, body, last modified, etc.
* */

//On update
/*
* Load notes into modal
* bind onSave btn to update local variable and send update request*/
/***call getAllNotes***/


//On delete
/*
* delete local variable and send delete request*/


/***call getAllNotes***/


//On create
/*
* create new note locally and send create request*/

/***call getAllNotes***/


//On logout
/**remove cookie**/































/******************Cookies*****************/
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
function updateNote(noteId){
    $("#myModal").modal('show');
    $("#noteTitle").val(titleData);
    var	handler = function(){
    updateData(noteId);
    $("#myModal").modal('hide');
	$("#saveChanges").unbind('click', handler);
};


$("#saveChanges").on('click', handler);
}

function updateData(noteId){
    titleData = $("#noteTitle").val();
}











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
//        user = prompt("Please enter your name:", "");
        alert("Welcome again " + user);
    } else {
        window.location = 'login.html';
        if (user != "" && user != null) {
            setCookie("username", user, 365);
        }
    }
}

