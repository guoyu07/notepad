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

        authenticate(userName,password,false);
    }
});

$('#signup').on('click',function () {
    var userName, password;
    userName = $('#username').val();
    password = $('#password').val();
    if(userName == "" || userName == null){
//TODO has-warning
    }else if(password == "" || password == null){
//TODO has-warning
    }else{

        authenticate(userName,password,true);
    }
});


//authenticate and set cookie
function authenticate(userName, password, isSignUp){
    var xhttp = new XMLHttpRequest();
    var outJson = {};
    if(Boolean(isSignUp)){
        outJson.identifier = "n";
    }else{
        outJson.identifier = "a";
    }
    outJson.userName = escapeSpaces(userName);
    outJson.password = password;
    $('#password').val("************************");
    xhttp.open("POST", cgiPath, true);
    xhttp.send(JSON.stringify(outJson));
    outJson = {}; password = "";

    xhttp.onreadystatechange = function () {
        if(this.readyState == 4 && this.status == 200){
            var inJson = JSON.parse(this.responseText);
            var areValid = Boolean(inJson.areValid);
            var lastLogin= inJson.lastLogin;

            if(areValid){
                $("#username").parent().addClass('has-success');
                $("#password").parent().addClass('has-success');
                console.log(userName, "is authenticated successfully")
                setCookie("uid",userName,1);
                setCookie("ll", lastLogin,1);
                if(lastLogin == "Never") alert('You have successfully signed up! \n Feel free to look around');
                checkCookie();
            }else{
                //throw error
                $("#username").parent().addClass('has-error');
                $("#password").parent().addClass('has-error');
                console.log(userName, "is not authenticated")
            }
        }
    };
}

//check cookie

/******************Cookies*****************/// Ref:http://www.w3schools.com/js/js_cookies.asp
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
    var user = getCookie("uid");
    if (user != "") {
            window.location = '../';
    }
}




//*****************Other functions*****************//

function escapeSpaces(str) {
    return str.replace(/ /g,'\\u0020');

}