/* Getting Started page templates */
#include "router_config.h"

/* Getting Started Page */
#define SETUP_CHUNK_HEAD "<html>\
<head>\
<meta name='viewport' content='width=device-width, initial-scale=1, maximum-scale=1, user-scalable=0'>\
<meta charset='UTF-8'>\
<title>Getting Started</title>\
<link rel='icon' href='favicon.png'>\
</head>\
<style>\
* { box-sizing: border-box; margin: 0; padding: 0; }\
body { font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif; background: linear-gradient(135deg, #0d000f 0%, #120020 100%); color: #cacad8; padding: 1rem; min-height: 100vh; line-height: 1.6; }\
h1 { font-size: 1.5rem; font-weight: 600; color: #a78bfa; margin-bottom: 1rem; text-shadow: 0 0 20px rgba(167, 139, 250, 0.3); }\
h2 { font-size: 1.15rem; font-weight: 500; color: #a78bfa; margin: 1.5rem 0 0.75rem 0; padding-bottom: 0.5rem; border-bottom: 1px solid rgba(167, 139, 250, 0.2); }\
#container { max-width: 500px; margin: 0 auto; padding: 1.5rem; background: rgba(15, 5, 24, 0.96); border-radius: 16px; box-shadow: 0 8px 32px rgba(0, 0, 0, 0.4); backdrop-filter: blur(10px); }\
table { width: 100%; border-collapse: collapse; }\
td { padding: 0.5rem 0; vertical-align: top; }\
td:first-child { color: #888; font-size: 0.9rem; padding-right: 0.75rem; width: 35%; text-align: right; }\
input[type='text'], input[type='password'] { width: 100%; background: rgba(28, 8, 44, 0.6); border: 1px solid rgba(167, 139, 250, 0.2); border-radius: 8px; color: #cacad8; padding: 0.75rem; font-size: 0.95rem; }\
input[type='text']:focus, input[type='password']:focus { outline: none; border-color: #a78bfa; box-shadow: 0 0 0 3px rgba(167, 139, 250, 0.15); background: rgba(28, 8, 44, 0.8); }\
input::placeholder { color: #666; }\
.ok-button { border: none; border-radius: 8px; padding: 0.75rem 1.5rem; font-size: 0.95rem; font-weight: 600; cursor: pointer; width: 100%; margin-top: 0.5rem; background: linear-gradient(135deg, #7c3aed 0%, #5b21b6 100%); color: #fff; box-shadow: 0 4px 15px rgba(124, 58, 237, 0.4); }\
.nav-link { display: inline-block; padding: 0.6rem 1.5rem; background: linear-gradient(135deg, #7c3aed 0%, #5b21b6 100%); color: #fff; border: none; border-radius: 8px; text-decoration: none; font-size: 0.9rem; font-weight: 600; margin-right: 0.5rem; }\
@media (max-width: 600px) { body { padding: 0.5rem; } #container { padding: 1rem; } h1 { font-size: 1.25rem; } h2 { font-size: 1rem; } td:first-child { font-size: 0.8rem; width: 40%; } input[type='text'], input[type='password'] { font-size: 0.9rem; padding: 0.65rem; } .ok-button { font-size: 0.9rem; padding: 0.65rem 1.25rem; } }\
</style>\
<body>\
<div id='container'>\
<div style='display: flex; align-items: center; margin-bottom: 0.5rem;'>\
<a href='/' style='display: inline-block; margin-right: 1rem;'><img src='/favicon.png' alt='Home' style='width: 64px; height: 64px; border: none;'></a>\
<h1 style='margin: 0;'>Getting Started</h1>\
</div>\
<script>\
var qs = window.location.search.substr(1);\
if (qs.indexOf('ap_ssid=') !== -1 || (qs.indexOf('ssid=') !== -1 && qs.indexOf('password=') !== -1)) {\
document.getElementById('container').style.display = 'none';\
document.body.innerHTML ='<div id=\"container\">' +\
'<h1>Setup Complete</h1>' +\
'<div style=\"text-align:center; margin:1.5rem 0;\">' +\
'<div style=\"font-size:3rem;\">&#10003;</div>' +\
'<h2 style=\"border:0; margin-top:0.5rem;\">Settings saved</h2>' +\
'<p>The repeater is restarting and connecting to your WiFi network.</p>' +\
'<p style=\"margin-top:1rem; color:#888;\">This setup network may disappear while the device restarts.</p>' +\
'<p style=\"margin-top:1rem;\">To manage the repeater again, try:</p>' +\
'<p style=\"margin-top:0.5rem;\"><a href=\"http://esp32-repeater.local/\" style=\"color:#a78bfa; font-weight:600;\">esp32-repeater.local</a></p>' +\
'<p style=\"margin-top:1rem; color:#888; font-size:0.9rem;\">If that does not work, check your router\\'s connected-device list for the repeater\\'s new IP address.</p>' +\
'</div></div>';\
}\
</script>"

/* Setup form - uses: safe_ap_ssid, safe_ssid */
#define SETUP_CHUNK_FORM "\
<form id='setupForm' action='/setup' method='GET'>\
<h2>Internet WiFi</h2>\
<p style='margin-bottom:1rem; color:#888; font-size:0.9rem;'>Choose the WiFi network this repeater should connect to.</p>\
<a href='/scan' class='nav-link' style='display:block; text-align:center; margin:0 0 1rem 0;'>Scan for WiFi Networks</a>\
<table>\
<tr><td>SSID</td><td><input id='sta_ssid' type='text' name='ssid' value='%s' placeholder='WiFi network'/></td></tr>\
<tr><td>Password</td><td><input id='sta_password' type='password' name='password' placeholder='WiFi password'/></td></tr>\
</table>\
<div style='margin:1.25rem 0; padding:1rem; background:rgba(28,8,44,0.6); border-radius:8px;'>\
<label style='display:flex; gap:0.75rem; align-items:center; cursor:pointer;'>\
<input id='sameWifi' type='checkbox' checked>\
<span>Repeat the same WiFi name and password</span>\
</label>\
</div>\
<div id='advancedAp' style='display:none;'>\
<h2>Repeated WiFi</h2>\
<p style='margin-bottom:1rem; color:#888; font-size:0.9rem;'>Use these settings only if you want the repeater to broadcast a different network name.</p>\
<table>\
<tr><td>SSID</td><td><input id='ap_ssid' type='text' name='ap_ssid' value='%s' placeholder='Repeated network name'/></td></tr>\
<tr><td>Password</td><td><input id='ap_password' type='password' name='ap_password' placeholder='Repeated network password'/></td></tr>\
</table>\
</div>\
<input type='submit' value='Save &amp; Reboot' class='ok-button'/>\
</form>\
<script>\
var same=document.getElementById('sameWifi');\
var advanced=document.getElementById('advancedAp');\
same.addEventListener('change',function(){advanced.style.display=this.checked?'none':'block';});\
document.getElementById('setupForm').addEventListener('submit',function(){\
if(same.checked){\
document.getElementById('ap_ssid').value=document.getElementById('sta_ssid').value;\
document.getElementById('ap_password').value=document.getElementById('sta_password').value;\
}\
});\
</script>\
<div style='margin-top:1.5rem; text-align:center;'>\
<a href='/' class='nav-link'>Home</a>\
</div>\
</div>\
</body>\
</html>"