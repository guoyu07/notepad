
var cells = Array.from(document.getElementById('table').children);
var playResponse = {};
var player =1;

cells.forEach(function (cell) {

	var handler = function(){
	        display(cell.id);
        	getPlayer();

	cell.removeEventListener('click',handler);
	};

    cell.addEventListener('click',handler);
});

var player1 = document.getElementById('p2Name');
player1.innerHTML = "Hello";


function getPlayer(){
    if(player == 1){
        player = 2;
    }else{
        player = 1;
    }
}


function display(id){
document.getElementById(id).innerHTML = id;
    playResponse= {
        "player": player,
        "position": id
    };
    console.log(JSON.stringify(playResponse));
}
