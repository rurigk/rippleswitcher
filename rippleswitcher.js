/*
*Dev: Gravyeth rurigkdev@gmail.com
*
*Firefox DNS flusher https://addons.mozilla.org/es/firefox/addon/dns-flusher/
*Repository: https://github.com/rurigk/rippleswitcher
*License: MIT
*
*/

const fs = require("fs");

const host_query = /#RippleSectionStart ---- Dont edit this section\n163\.172\.71\.251 osu\.ppy\.sh\n163\.172\.71\.251 c\.ppy\.sh\n163\.172\.71\.251 c1\.ppy\.sh\n163\.172\.71\.251 a\.ppy\.sh\n163\.172\.71\.251 i\.ppy\.sh\n37\.187\.125\.67 bm6\.ppy\.sh\n#RippleSectionEnd/g;
const ripple_host = "#RippleSectionStart ---- Dont edit this section\n163.172.71.251 osu.ppy.sh\n163.172.71.251 c.ppy.sh\n163.172.71.251 c1.ppy.sh\n163.172.71.251 a.ppy.sh\n163.172.71.251 i.ppy.sh\n37.187.125.67 bm6.ppy.sh\n#RippleSectionEnd";

var switchhost = (process.argv.indexOf("switch") >= 0)? true:false;

function ReadHosts(){
	return fs.readFileSync("/etc/hosts","utf8");
}
function SwitchRipple(){
	var hostf = ReadHosts();
	if(host_query.test(hostf)){
		//Switch ripple off
		hostf = hostf.replace(host_query,"");
		fs.writeFileSync("/etc/hosts",hostf);
		console.log("You are now in osu! servers");
	}else{
		//Switch ripple on
		hostf += ripple_host;
		fs.writeFileSync("/etc/hosts",hostf);
		console.log("You are now in Ripple servers");
	}
}
if(switchhost){
	if(typeof process.env.SUDO_UID != "undefined"){
		SwitchRipple();
	}else{
		console.log("You need run this as root");
	}
}else{
	var hostf = ReadHosts();
	if(host_query.test(hostf)){
		console.log("You are in Ripple servers");
	}else{
		console.log("You are in osu! servers");
	}
}


