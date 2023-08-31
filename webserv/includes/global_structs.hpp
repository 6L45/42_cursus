#pragma once

# include "common.hpp"

typedef struct s_ret_200
{
	std::map<int, std::string>	ret;

	s_ret_200 ()
	{
		ret.insert(std::make_pair(200, "OK")),
		ret.insert(std::make_pair(201, "Created"));
		ret.insert(std::make_pair(202, "Accepted"));
		ret.insert(std::make_pair(203, "Non-Authoritative Information"));
		ret.insert(std::make_pair(204, "No Content"));
		ret.insert(std::make_pair(205, "Reset Content"));
		ret.insert(std::make_pair(206, "Partial Content"));
		ret.insert(std::make_pair(207, "Multi-Status"));
		ret.insert(std::make_pair(208, "Already Reported"));
		ret.insert(std::make_pair(210, "Content Different"));
		ret.insert(std::make_pair(226, "IM Used"));
	}

	std::string	operator[](int n)
		{ return (ret[n]); }

} t_ret;

typedef struct s_errs
{
	std::map<int, std::string>	errs;

	s_errs ()
	{
		// 100
		errs.insert(std::make_pair(100, "Continue")),
		errs.insert(std::make_pair(101, "Switching Protocol"));
		errs.insert(std::make_pair(102, "Processing"));
		errs.insert(std::make_pair(103, "Early Hints"));

		// 300
		errs.insert(std::make_pair(300, "Multiple Choices")),
		errs.insert(std::make_pair(301, "Moved Permanently"));
		errs.insert(std::make_pair(302, "Found"));
		errs.insert(std::make_pair(303, "See Other"));
		errs.insert(std::make_pair(304, "Not Modified"));
		errs.insert(std::make_pair(305, "Use Proxy"));
		errs.insert(std::make_pair(307, "Temporary Redirect"));
		errs.insert(std::make_pair(308, "Permanent Redirect"));
		errs.insert(std::make_pair(310, "Too Many Redirects"));
	
		// 400
		errs.insert(std::make_pair(400, "Bad Request")),
		errs.insert(std::make_pair(401, "Unauthorized"));
		errs.insert(std::make_pair(402, "Payment Required"));
		errs.insert(std::make_pair(403, "Forbidden"));
		errs.insert(std::make_pair(404, "Not Found"));
		errs.insert(std::make_pair(405, "Method Not Allowed"));
		errs.insert(std::make_pair(406, "Not Acceptable"));
		errs.insert(std::make_pair(407, "Proxy Authentication Requiered"));
		errs.insert(std::make_pair(408, "Request Time-out"));
		errs.insert(std::make_pair(409, "Conflict"));
		errs.insert(std::make_pair(410, "Gone"));
		errs.insert(std::make_pair(411, "Length Required"));
		errs.insert(std::make_pair(412, "Precondition Failed"));
		errs.insert(std::make_pair(413, "Request Entity Too Large"));
		errs.insert(std::make_pair(414, "Request-URI Too Long"));
		errs.insert(std::make_pair(415, "Unsuported Media Type"));
		errs.insert(std::make_pair(416, "Request range unsastifiable"));
		errs.insert(std::make_pair(417, "Expectation failed"));
		errs.insert(std::make_pair(421, "Misdirected Request"));
		errs.insert(std::make_pair(422, "Unprocessable entity"));
		errs.insert(std::make_pair(423, "Locked"));
		errs.insert(std::make_pair(424, "Failed Dependancy"));
		errs.insert(std::make_pair(425, "Unordered Collection"));
		errs.insert(std::make_pair(426, "Upgrade Requiered"));
		errs.insert(std::make_pair(428, "Precondition Requiered"));
		errs.insert(std::make_pair(429, "Too Many Requests"));
		errs.insert(std::make_pair(431, "Request Header Fields Too Large"));
		errs.insert(std::make_pair(449, "Retry With"));
		errs.insert(std::make_pair(450, "Blocked by Windows Parental Controls"));
		errs.insert(std::make_pair(451, "Unavailable For Legal Reasons"));
		errs.insert(std::make_pair(456, "Unrecoverable Error"));

		// 500
		errs.insert(std::make_pair(500, "Internal Server Error")),
		errs.insert(std::make_pair(501, "Not Implemented"));
		errs.insert(std::make_pair(502, "Bad Gateway"));
		errs.insert(std::make_pair(503, "Service Unavailable"));
		errs.insert(std::make_pair(504, "Gateway Time-out"));
		errs.insert(std::make_pair(505, "HTTP Version not Supported"));
		errs.insert(std::make_pair(506, "Variant Also Negotiates"));
		errs.insert(std::make_pair(507, "Insufficient storage"));
		errs.insert(std::make_pair(508, "Loop detected"));
		errs.insert(std::make_pair(509, "Bandwidth Limit Exceeded"));
		errs.insert(std::make_pair(510, "Not extended"));
		errs.insert(std::make_pair(511, "Network authentication requiered"));
	}

	std::string	&operator[](int n)
		{ return (errs[n]); }

} t_errs;

typedef struct links
{
	std::vector<std::string>	hehe;

	links()
	{
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/Rkis28kMJd1aE\" width=\"480\" height=\"317\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/uprwwjptZW4Za\" width=\"480\" height=\"358\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/9ZOyRdXL7ZVKg\" width=\"480\" height=\"360\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/ReImZejkBnqYU\" width=\"480\" height=\"270\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/R195TgCcRZNZe\" width=\"480\" height=\"271\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe><p></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/1iTI7wQfPEJu1wjK\" width=\"480\" height=\"271\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/WVUWw9ItZS048\" width=\"480\" height=\"305\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/XymaJlgorUL8vOfF88\" width=\"480\" height=\"400\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/mGbjatyEFVxdDRnQ9U\" width=\"480\" height=\"270\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/spfi6nabVuq5y\" width=\"480\" height=\"392\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/15aGGXfSlat2dP6ohs\" width=\"480\" height=\"272\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/kd9h44W2CpZBLH7QpA\" width=\"360\" height=\"480\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/SANT0ESrslle7yE9xV\" width=\"480\" height=\"270\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/RGSZZQC7SSc91VhDe7\" width=\"480\" height=\"270\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/fvfRNXU8gkH0sLvDzQ\" width=\"480\" height=\"270\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/3Fdskc7J0timI\" width=\"480\" height=\"270\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/Yycc82XEuWDaLLi2GV\" width=\"480\" height=\"400\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		hehe.push_back("		<center><iframe src=\"https://giphy.com/embed/ftqLysT45BJMagKFuk\" width=\"480\" height=\"405\" frameBorder=\"0\" class=\"giphy-embed\" allowFullScreen></iframe></center>");
		
		hehe.shrink_to_fit();
	}

	std::string	operator[](int n)
	{
		if (n)
			return ( hehe[std::rand() % (hehe.size())] );
		return ( hehe[std::rand() % (hehe.size())] );
	}

} memelord;

enum	ext_category
{
	NORM = 1,
	BIN
};

typedef struct	ExTypes
{
	std::map<std::string, std::string>	ext_type;

	ExTypes()
	{
		ext_type["log"]		= "text/plain";
		ext_type["ics"]		= "text/calendar";
		ext_type["csv"]		= "text/csv";
		ext_type["html"]	= "text/html";
		ext_type["htm"]		= "text/html";
		ext_type["shtml"]	= "text/html";
		ext_type["css"]		= "text/css";
		ext_type["xml"]		= "text/xml";
		ext_type["mml"]		= "text/mathml";
		ext_type["txt"]		= "text/plain";
		ext_type["jad"]		= "text/vnd.sun.j2me.app-descriptor";
		ext_type["wml"]		= "text/vnd.wap.wml";
		ext_type["htc"]		= "text/x-component";

		ext_type["gif"]		= "image/gif";
		ext_type["jpg"]		= "image/jpeg";
		ext_type["jpeg"]	= "image/jpeg";
		ext_type["png"]		= "image/png";
		ext_type["svg"]		= "image/svg+xml";
		ext_type["svgz"]	= "image/svg+xml";
		ext_type["tif"]		= "image/tiff";
		ext_type["tiff"]	= "image/tiff";
		ext_type["wbmp"]	= "image/vnd.wap.wbmp";
		ext_type["webp"]	= "image/webp";
		ext_type["ico"]		= "image/x-icon";
		ext_type["jng"]		= "image/x-jng";
		ext_type["bmp"]		= "image/x-ms-bmp";

		ext_type["woff"]	= "font/woff";
		ext_type["woff2"]	= "font/woff2";

		ext_type["xul"]		= "application/vnd.mozilla.xul+xml";
		ext_type["epub"]	= "application/epub+zip";
		ext_type["mpkg"]	= "application/vnd.apple.installer+xml";
		ext_type["azw"]		= "application/vnd.amazon.ebook";
		ext_type["bz"]		= "application/x-bzip";
		ext_type["bz2"]		= "application/x-bzip2";
		ext_type["csh"]		= "application/x-csh";
		ext_type["arc"]		= "application/octet-stream";
		ext_type["abw"]		= "application/x-abiword";
		ext_type["js"]		= "application/javascript";
		ext_type["atom"]	= "application/atom+xml";
		ext_type["rss"]		= "application/rss+xml";
		ext_type["jar"]		= "application/java-archive";
		ext_type["war"]		= "application/java-archive";
		ext_type["ear"]		= "application/java-archive";
		ext_type["json"]	= "application/json";
		ext_type["hqx"]		= "application/mac-binhex40";
		ext_type["doc"]		= "application/msword";
		ext_type["pdf"]		= "application/pdf";
		ext_type["ps"]		= "application/postscript";
		ext_type["eps"]		= "application/postscript";
		ext_type["ai"]		= "application/postscript";
		ext_type["rtf"]		= "application/rtf";
		ext_type["m3u8"]	= "application/vnd.apple.mpegurl";
		ext_type["kml"]		= "application/vnd.google-earth.kml+xml";
		ext_type["kmz"]		= "application/vnd.google-earth.kmz";
		ext_type["xls"]		= "application/vnd.ms-excel";
		ext_type["eot"]		= "application/vnd.ms-fontobject";
		ext_type["ppt"]		= "application/vnd.ms-powerpoint";
		ext_type["odg"]		= "application/vnd.oasis.opendocument.graphics";
		ext_type["odp"]		= "application/vnd.oasis.opendocument.presentation";
		ext_type["ods"]		= "application/vnd.oasis.opendocument.spreadsheet";
		ext_type["odt"]		= "application/vnd.oasis.opendocument.text";
		ext_type["pptx"]	= "application/vnd.openxmlformats-officedocument.presentationml.presentation";
		ext_type["xlsx"]	= "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
		ext_type["docx"]	= "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
		ext_type["wmlc"]	= "application/vnd.wap.wmlc";
		ext_type["7z"]		= "application/x-7z-compressed";
		ext_type["cco"]		= "application/x-cocoa";
		ext_type["jardiff"]	= "application/x-java-archive-diff";
		ext_type["jnlp"]	= "application/x-java-jnlp-file";
		ext_type["run"]		= "application/x-makeself";
		ext_type["pl"]		= "application/x-perl";
		ext_type["pm"]		= "application/x-perl";
		ext_type["prc"]		= "application/x-pilot";
		ext_type["pdb"]		= "application/x-pilot";
		ext_type["rar"]		= "application/x-rar-compressed";
		ext_type["rpm"]		= "application/x-redhat-package-manager";
		ext_type["sea"]		= "application/x-sea";
		ext_type["swf"]		= "application/x-shockwave-flash";
		ext_type["sit"]		= "application/x-stuffit";
		ext_type["tcl"]		= "application/x-tcl";
		ext_type["tk"]		= "application/x-tcl";
		ext_type["der"]		= "application/x-x509-ca-cert";
		ext_type["pem"]		= "application/x-x509-ca-cert";
		ext_type["crt"]		= "application/x-x509-ca-cert";
		ext_type["xpi"]		= "application/x-xpinstall";
		ext_type["xhtml"]	= "application/xhtml+xml";
		ext_type["xspf"]	= "application/xspf+xml";
		ext_type["zip"]		= "application/zip";
		ext_type["ogx"]		= "application/ogg";
		ext_type["sh"]		= "application/x-sh";
		ext_type["tar"]		= "application/x-tar";
		ext_type["ttf"]		= "application/x-font-ttf";
		ext_type["vsd"]		= "application/vnd.visio";

		ext_type["bin"]		= "application/octet-stream";
		ext_type["exe"]		= "application/octet-stream";
		ext_type["dll"]		= "application/octet-stream";
		ext_type["deb"]		= "application/octet-stream";
		ext_type["dmg"]		= "application/octet-stream";
		ext_type["iso"]		= "application/octet-stream";
		ext_type["img"]		= "application/octet-stream";
		ext_type["msi"]		= "application/octet-stream";
		ext_type["msp"]		= "application/octet-stream";
		ext_type["msm"]		= "application/octet-stream";

		ext_type["oga"]		= "audio/ogg";
		ext_type["wav"]		= "audio/x-wav";
		ext_type["weba"]	= "audio/webm";
		ext_type["aac"]		= "audio/aac";
		ext_type["mid"]		= "audio/midi";
		ext_type["midi"]	= "audio/midi";
		ext_type["kar"]		= "audio/midi";
		ext_type["mp3"]		= "audio/mpeg";
		ext_type["ogg"]		= "audio/ogg";
		ext_type["m4a"]		= "audio/x-m4a";
		ext_type["ra"]		= "audio/x-realaudio";

		ext_type["3g2"]		= "video/3gpp2 audio/3gpp2";

		ext_type["ogv"]		= "video/ogg";
		ext_type["3gpp"]	= "video/3gpp";
		ext_type["3gp"]		= "video/3gpp";
		ext_type["ts"]		= "video/mp2t";
		ext_type["mp4"]		= "video/mp4";
		ext_type["mpeg"]	= "video/mpeg";
		ext_type["mpg"]		= "video/mpeg";
		ext_type["mov"]		= "video/quicktime";
		ext_type["webm"]	= "video/webm";
		ext_type["flv"]		= "video/x-flv";
		ext_type["m4v"]		= "video/x-m4v";
		ext_type["mng"]		= "video/x-mng";
		ext_type["asx"]		= "video/x-ms-asf";
		ext_type["asf"]		= "video/x-ms-asf";
		ext_type["wmv"]		= "video/x-ms-wmv";
		ext_type["avi"]		= "video/x-msvideo";
	}

	std::string	get_type(std::string path, std::string extension)
	{
		struct stat	path_stat;
		stat(path.c_str(), &path_stat);

		if (extension.empty() && path_stat.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
			extension = "exe";

		std::map<std::string, std::string>::iterator it = ext_type.find(extension);
		
		if (it != ext_type.end())
			return (it->second);

		return (std::string());
	}

	std::string	get_type(std::string extension)
	{
		if (extension.empty())
			return (extension);
		
		std::map<std::string, std::string>::iterator it = ext_type.find(extension);
		if (it == ext_type.end())
			return (extension);

		return (it->second);
	}

	int get_category(std::string path, std::string extension)
	{
		struct stat	path_stat;
		stat(path.c_str(), &path_stat);

		if (S_ISDIR(path_stat.st_mode) ||
			(extension.empty() && path_stat.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
			return (BIN);
		std::string	type = this->get_type(path, extension);

		if (type.find("text") != std::string::npos)
			return (NORM);
	
		return (BIN);
	}
}	t_ext;



/*
In HTTP, the Transfer-Encoding field is used to indicate that the body
of a request or response is encoded using a specific encoding mechanism.
If the Transfer-Encoding field is present in a request or response and
the value is set to chunked, it indicates that the body of the message
is divided into chunks and each chunk is encoded separately.
Whether the server should chunk the response or not depends on how
the server is implemented and the requirements of the response.
The chunked encoding can be useful in situations where the size of the data
is not known upfront, such as when generating dynamic content on the fly
or when streaming data from a source that does not provide the size of the data in advance.
In the case of a 404 Not Found error, it is not necessarily required for the server
to use the chunked encoding. It is up to the server implementation to decide how to encode
the body of the response. If the size of the data in the body of the response is known
in advance, the server can include the Content-Length field in the response headers
to specify the size of the data. If the size of the data is not known in advance,
the server can use the chunked encoding or use some other encoding mechanism.
It's worth noting that the Transfer-Encoding field is not allowed to be used in HTTP responses
if the Content-Length field is also present. If both fields are present in a response,
the Content-Length field takes precedence and the Transfer-Encoding field is ignored.
It's not clear from the information you provided why the Transfer-Encoding header is expected
to be present in the response for the test case you mentioned.
It might be helpful to review the implementation of the server
and the requirements of the test case to understand the reasoning behind the assertion.
*/