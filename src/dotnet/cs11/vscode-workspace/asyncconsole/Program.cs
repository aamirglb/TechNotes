HttpClient client = new();

HttpResponseMessage r2 = await client.GetAsync("http://www.apple.com/");
WriteLine("apple homepage has {0:N0} bytes", r2.Content.Headers.ContentLength);

HttpResponseMessage response = await client.GetAsync("http://www.google.com/");
WriteLine("google's home page has {0:N0} bytes", response.Content.Headers.ContentLength);



