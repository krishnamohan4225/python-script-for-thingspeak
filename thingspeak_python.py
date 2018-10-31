import urllib.request
import json
import time
from pprint import pprint

while True:
  TS = urllib.request.urlopen("https://api.thingspeak.com/channels/615641/feeds.json?results=1")
  response = TS.read()
  data=json.loads(response)
  b= data['feeds'][0]['field1']
  print ("distance is : " + b)
  time.sleep(5)
  TS.close()
