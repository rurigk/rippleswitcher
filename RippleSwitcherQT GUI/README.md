# RippleSwitcherQt
Linux ripple switcher (Qt version)

You need install certificates in wine manually

###Running

Open with root privileges on terminal or use RippleSwitcher.sh shell file

You may need QT4 runtime for run (libqt4)
```bash
sudo apt-get install libqt4-core libqt4-gui libqt4-svg
```
###Building source

Open project file in QtCreator and build
QT4 required

###Notes

Some times when return to osu servers the web browser not update the DNS cache and redirect osu.ppy.sh to ripple.moe

On firefox use [Firefox DNS flusher](https://addons.mozilla.org/es/firefox/addon/dns-flusher/) add-on

On chrome navigate to [chrome://net-internals/#dns](chrome://net-internals/#dns) and press the "Clear host cache" button.

##Install certificate
Download certificate
[Ripple Certificate](https://git.zxq.co/ripple/ripple-server-switcher/raw/master/RippleServerSwitcher/Resources/certificate.cer)

Open the Internet Explorer configuration by running
```
wine control
```
Double click the Internet Settings icon, navigate to the Content tab, then click the Certificates… button.    
Click on Import, then Next.    
Click Browse… then select the Ripple certificate.    
Click Next.    
Select Place all certificates in the following store, and click Browse.    
Select Trusted Root Certification Authorities, and click Ok.    
Click Next, Finish.    
You should get a message saying The import was successful.    
After that is done, you can start the client up, and log in with your Ripple credentials.    

