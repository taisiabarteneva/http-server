#!/usr/bin/python
import time

time = time.asctime(time.localtime())

body = '<html><body>\nServer time is ' + time + '\n</body></html>'
# This is the message that contains the cookie
# and will be sent in the HTTP header to the client

# To save one line of code
# we replaced the print command with a '\n'
# print (c)
print ('Content-Type: text/html\r')
print ('Set-Cookie: lastvisit=' + time + "\r")
print ('Content-Length: ' + str(len(body)) + '\r\n\r')
# End of HTTP header

print (body)

# print ('<html><body>')
# print ('Server time is', time.asctime(time.localtime()))
# print ('</body></html>')
