#ifndef MIME_TYPES_H
#define MIME_TYPES_H

enum content_mime_type {
	// Documentos Web
	TYPE_HTML, TYPE_CSS, TYPE_JS, TYPE_PHP,
	
    // Imagens
	TYPE_PNG, TYPE_JPG, TYPE_GIF,
    TYPE_SVG, TYPE_ICO, TYPE_WEBP,
	
    // Dados
	TYPE_JSON, TYPE_XML, TYPE_CSV,
	
    // Fontes
	TYPE_WOFF, TYPE_WOFF2, TYPE_TTF,
	
    // Mídia
	TYPE_MP3, TYPE_MP4, TYPE_WAV,
	
    // Documentos
	TYPE_PDF, TYPE_ZIP,	TYPE_DOCX,
	
    // Fallback
	TYPE_OCTET_STREAM, TYPE_UNKNOWN
};

struct mime_mapping {
	enum content_mime_type type;
	const char *extension;
	const char *mime_str;
};

// Declaração da função
const char *get_mime_string(enum content_mime_type type);
enum content_mime_type get_type_from_filename(const char *filename);

#endif
