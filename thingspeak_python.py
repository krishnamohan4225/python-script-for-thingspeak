import urllib.request as req
response = req.urlopen('https://api.thingspeak.com/channels/556464/feeds.json?results=1')
print (response.read())


import urllib.request
import json
import time
from pprint import pprint

while True:
  TS = urllib.request.urlopen("https://api.thingspeak.com/channels/556464/feeds.json?results=1")

  response = TS.read()
  data=json.loads(response)
  b= data['feeds'][0]['field1']
  print (b)
  time.sleep(5)
  TS.close()
