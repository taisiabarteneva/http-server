
// Instantiating new EasyHTTP class
const http = new DeleteHTTP;
  
// Update Post
http.delete('/files/22.png')
  
// Resolving promise for response data
.then(data => console.log(data))
  
// Resolving promise for error
.catch(err => console.log(err));