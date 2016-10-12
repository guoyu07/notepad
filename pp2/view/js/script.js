
var cgiPath = "cgi-bin/ttt.cgi";

var playerList = {};

var shootJson = {};

var tmp_player = {
    1:{}, 2:{}

};
var player = {
    1:{}, 2:{}

};

var sel1 = document.getElementById('sel1');
var sel2 = document.getElementById('sel2');

var btn1 = document.getElementById('btn1');
var btn2 = document.getElementById('btn2');

var are_players_set = false;

var cells = Array.from(document.getElementById('table').children);
var playResponse = {};

var player_num =1;


//Fetch all players
getAllPlayers();

//Event listeners for board
cells.forEach(function (cell) {

	var handler = function(){
        if(are_players_set) {
            display(cell.id);
            getPlayer();
        }

	cell.removeEventListener('click',handler);
	};

    cell.addEventListener('click',handler);
});

//TODO check if other tmp_player is also set? then change @are_players_set to true
//Event listeners for tmp_player dropdown fields
sel1.addEventListener('change',function () {
    updatePlayerByDD(this, 'p1_n', 'p1_m','playerSel1');
});
sel2.addEventListener('change',function () {
    updatePlayerByDD(this, 'p2_n', 'p2_m','playerSel2');
});

//Event listeners for 'done' buttons
//TODO call cgi to validate and print tmp_player names from response
btn1.addEventListener('click',function () {
    updatePlayerByForm(1,'usr1','mrkr1','playerSel1');
});

btn2.addEventListener('click',function () {
    updatePlayerByForm(2,'usr2','mrkr2','playerSel2');
});





function getPlayer(){
    if(player_num == 1){
        player_num = 2;
    }else{
        player_num = 1;
    }
}


function display(id){
document.getElementById(id).innerHTML = id;
    playResponse= {
        "player": player_num,
        "position": id
    };
    console.log(JSON.stringify(playResponse));
}


function getAllPlayers(){
    var xhttp = new XMLHttpRequest();
    var outJson = {};
    outJson.identifier="G";

    xhttp.open("POST",cgiPath,true);
    xhttp.send(JSON.stringify(outJson));


    xhttp.onreadystatechange = function () {
        if(this.readyState == 4 && this.status == 200) {
            var inJson = JSON.parse(this.responseText);
            playerList = inJson.players;

            inJson.players.forEach(function (player) {
                var listItem = document.createElement("option");var listItem2 = document.createElement("option");
                var item = document.createTextNode(player.name + " (" + player.marker + ")");var item2 = document.createTextNode(player.name + " (" + player.marker + ")");
                listItem.appendChild(item);listItem2.appendChild(item2);
                sel1.appendChild(listItem);
                sel2.appendChild(listItem2);
            })

            //TODO uncomment this if necessary
            // document.getElementById('p1_n').innerHTML = playerList[sel1.selectedIndex].name;
            // document.getElementById('p1_m').innerHTML = playerList[sel1.selectedIndex].marker;
            // document.getElementById('p2_n').innerHTML = playerList[sel2.selectedIndex].name;
            // document.getElementById('p2_m').innerHTML = playerList[sel2.selectedIndex].marker;
        }
    };


}

function updatePlayerByDD(dropdown, p_name, p_marker,p_form){
    if(dd.selectedIndex == 0) return;
    console.log(playerList[dd.selectedIndex]);
    tmp_player[playerId].name = playerList[dd.selectedIndex-1].name;
    tmp_player[playerId].marker = playerList[dd.selectedIndex-1].marker;
    document.getElementById(p_name).innerHTML = playerList[dd.selectedIndex-1].name;
    document.getElementById(p_marker).innerHTML = playerList[dd.selectedIndex-1].marker;
    document.getElementById(p_form).setAttribute('class','done');

}

function updatePlayerByForm(playerId, name_field, marker_field,form_class){
    tmp_player[playerId].name = document.getElementById(name_field).value;
    tmp_player[playerId].marker = document.getElementById(marker_field).value;

    if(tmp_player[playerId].name != "" && tmp_player[playerId].marker != "") {
        document.getElementById(form_class).setAttribute('class','done');
    }else{
        alert('Name or marker can\'t be empty fields');
    }
}


function validatePlayers(){
    var xhttp = new XMLHttpRequest();

    xhttp.open("POST",cgiPath,true);
    var outJson ={};
    outJson.identifier = "V";
    outJson.player1_name = tmp_player[1].name;
    outJson.player1_marker = tmp_player[1].marker;
    outJson.player2_name = tmp_player[2].name;
    outJson.player2_marker = tmp_player[2].marker;
    xhttp.send(JSON.stringify(outJson));

    xhttp.onreadystatechange = function () {
        var inJson = JSON.parse(this.responseText);
        if(tmp_player[1].)
    }


}