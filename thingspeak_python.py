import urllib.request as req
response = req.urlopen('https://api.thingspeak.com/channels/556464/feeds.json?results=1')
print (response.read())


