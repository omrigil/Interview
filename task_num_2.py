import http.server as BaseHTTPServer
import os
from ssl import wrap_socket
import argparse

parser = argparse.ArgumentParser(description="this script run http server that serves files for download")
parser.add_argument("file_path", nargs='?', type=str, default=__file__,
                    help="Directory to served files from (Default:current directory.)")
parser.add_argument("port", nargs='?', type=int, default=8000, help="Port (Default: 8000)")
parser.add_argument("HTTP", nargs='?', type=str, default="1.1", help="HTTP version (1 / 1.1 / 2 /...)")
parser.add_argument("HTTPS", nargs='?', type=str, default="Not required",
                    help="If HTTPS is required, directory with certificate (key.pem/cert.pem)")

args = parser.parse_args()
file_path = args.file_path  # pas the users arguments


class MyHTTPRequestHandler(BaseHTTPServer.BaseHTTPRequestHandler):
    def do_GET(self):
        with open(file_path, 'rb') as f:
            self.send_response(200)   #
            self.send_header("Content-Type", 'application/octet-stream')
            file_name = os.path.basename(file_path)  # get the filename from the path.
            self.send_header("Content-Disposition", 'attachment; filename="{}"'.format(file_name))
            if "no_length" not in file_name:   # check if the file name containing the sub-string "no_length"
                f_stat = os.fstat(f.fileno())
                self.send_header("Content-Length", str(f_stat.st_size))  # send the size of the file.
            self.end_headers()
            chunk = 4096   # Divide the file to chunk of 4096 and send them one by one.
            rf_chunk = f.read(chunk)  # copy the file and response him to the client.
            while len(rf_chunk) > 0:
                self.wfile.write(rf_chunk)
                rf_chunk = f.read(chunk)


def run(handler_class=MyHTTPRequestHandler, server_class=BaseHTTPServer.HTTPServer, protocol="HTTP/" + args.HTTP):
    port = args.port    # get the port that the user request
    server_address = ('', port)
    handler_class.protocol_version = protocol
    httpd = server_class(server_address, handler_class)
    if args.HTTPS != "Not required":   # check if needed https or not
        httpd.socket = wrap_socket(httpd.socket,
                                   keyfile=os.path.join(args.HTTPS, "key.pem"),
                                   certfile=os.path.join(args.HTTPS, "cert.pem"),
                                   server_side=True)
    httpd.serve_forever()


if __name__ == '__main__':
    run()
