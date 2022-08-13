FROM alpine:3.14

RUN	apk update && apk upgrade && apk add --no-cache \
        nginx \
        openssl

# nginx SSL
RUN mkdir /etc/nginx/ssl


# https://www.openssl.org/docs/man1.0.2/man1/openssl-req.html
# The req command primarily creates and processes certificate requests in PKCS#10 format.
# It can additionally create self signed certificates for use as root CAs for example.

RUN openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
        -out /etc/nginx/ssl/mberengu.pem \
        -keyout /etc/nginx/ssl/mberengu.key \
        -subj "/C=FR/ST=PACA/L=NICE/O=42Nice/OU=mberengu/CN=mberengu.42.fr/"

# -newkey arg
#       this option creates a new certificate request and a new private key.
# -out filename
#       This specifies the output filename to write to or standard output by default.
# -keyout filename
#       this gives the filename to write the newly created private key to
# -subj arg
#       sets subject name for new request or supersedes the subject name when processing a request.

RUN mkdir -p /run/nginx
COPY conf/nginx.conf /etc/nginx/http.d/default.conf

# Start nginx
ENTRYPOINT ["nginx", "-g", "daemon off;"]
