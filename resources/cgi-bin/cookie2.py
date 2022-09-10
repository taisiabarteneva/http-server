import time

# This is the message that contains the cookie
# and will be sent in the HTTP header to the client
print 'Set-Cookie: lastvisit=' + str(time.time()) + "\r\n";

# To save one line of code
# we replaced the print command with a '\n'
print 'Content-Type: text/html\r\n'
print 'Content-Length: 30\r\n\r\n'
# End of HTTP header

print '<html><body>'
print 'Server time is', time.asctime(time.localtime())
print '</body></html>'