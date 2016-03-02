# AppstreamPopcon

This little program will turn any traditional popcon resource into a traditional popcon information db into one with the same data but which uses appstream identifiers.

## Usage
You just need to pass the url that it will fetch the information from. Pipe to `gzip` if you need it to provide the information compressed, like it usually does:
```
appstreampopcon http://popcon.debian.org/all-popcon-results.gz | gzip -c > appstream-popcon.gz
```
