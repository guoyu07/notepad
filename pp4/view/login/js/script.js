/**
 * Created by rchowda on 11/20/2016.
 */
var cgiPath = "../cgi-bin/notes.cgi";
window.addEventListener("load", onLoadFunction);

function onLoadFunction() {
    checkCookie();
}

$('#login').on('click',function () {
    var userName, password;
    userName = $('#username').val();
    password = $('#password').val();
    if(userName == "" || userName == null){
//TODO has-warning
    }else if(password == "" || password == null){
//TODO has-warning
    }else{

        authenticate(userName,password);
    }
});

//authenticate and set cookie
function authenticate(userName, password){
    var xhttp = new XMLHttpRequest();
    var outJson = {};
    outJson.identifier = "a";
    outJson.userName = escapeSpaces(userName);
    outJson.password = password;
    $('#password').val("************************");
    xhttp.open("POST", cgiPath, true);
    xhttp.send(JSON.stringify(outJson));
    console.log("Sentout request", JSON.stringify(outJson));
    outJson = {}; password = "";

    xhttp.onreadystatechange = function () {
        if(this.readyState == 4 && this.status == 200){
            var inJson = JSON.parse(this.responseText);
            var areValid = Boolean(inJson.areValid);

            if(areValid){
                console.log(userName, "is authenticated successfully")
                setCookie("uid",userName,1);
                checkCookie();
            }else{
                //throw error
                console.log(userName, "is not authenticated")
            }
        }
    };
}

//check cookie

/******************Cookies*****************/
function setCookie(cname, cvalue, exdays) {
    console.log("setting cookie", cname, cvalue, exdays);
    var d = new Date();
    d.setTime(d.getTime() + (exdays*24*60*60*1000));
    var expires = "expires="+d.toUTCString();
    document.cookie = cname + "=" + cvalue + ";" + expires + ";path=../";
}

function getCookie(cname) {
    console.log("fetching cookie", cname);
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
    var user = getCookie("uid");
    if (user != "") {
        // user = prompt("Please enter your name:", "");
        alert("Welcome again " + user);

            window.location = '../';

    } else {
        console.log("no cookie found");
        // if (user != "" && user != null) {
        //     setCookie("username", user, 1);
        // }
    }
}




//*****************Other functions*****************//

function escapeSpaces(str) {
    return str.replace(/ /g,'\\u0020');

}