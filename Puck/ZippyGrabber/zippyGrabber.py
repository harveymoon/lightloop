import sys
import tweepy
import serial

#Setup Twitter
auth = tweepy.OAuthHandler('9Ydmrsqv1ZKd3I4YBmFoicj7h', '6k1LHl3Qe9WdSqXFRfwxksXiLTpFpZDZGmVaFoYqmcKRKPypKK')
auth.set_access_token('260019594-JWiNrD02XAd8tzm2QeyHCQjEl9rbdv085bLnu4f2', '0j6pW5M8ivQSIRYt3qCo3voaMkBiAhHkHwNcZh0EO8rEG')
api = tweepy.API(auth)

#Setup Serial Port

ser = serial.Serial('/dev/cu.usbmodem1411', 9600)

class CustomStreamListener(tweepy.StreamListener):
    def on_status(self, status):
        if 'dave' in status.text.lower():
            ser.write('1')
        elif 'boat' in status.text.lower():
            ser.write('2')

    def on_error(self, status_code):
        print >> sys.stderr, 'Encountered error with status code:', status_code
        return True # Don't kill the stream

    def on_timeout(self):
        print >> sys.stderr, 'Timeout...'
        return True # Don't kill the stream

sapi = tweepy.streaming.Stream(auth, CustomStreamListener())
sapi.filter(track = ['laser', 'dip'], locations=[-6.38,49.87,1.77,55.81])

