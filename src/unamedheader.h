#include <iostream>
#include <string>
#include <map>
#include <pair>

#if defined(ARC16)
	#define WORD_TYPE int_16t
	#define U_WORD_TYPE uint_16t
#elif defined(ARC32)
	#define WORD_TYPE int_32t
	#define U_WORD_TYPE uint_32t
#elif defined(ARC64)
	#define WORD_TYPE int_64t
	#define U_WORD_TYPE uint_64t
#endif

/*
#if defined(_WINDOWS_)
	#include
#elif defined(_UNIX_)
	#include
#elif defined(_MACH_)
	#include
#endif
*/

class color_space;
class pix;
class pixrow;
class pixblock;
class image_stack;
class tool;
class tool_map;
class codec;
class codec_map;
class mangler;
class mang_map;
class map_populator;

typedef std::pair<string, unsigned int> color_space_key_pairing;
typedef void (*tool_function)(std::string *);

class file
{
public:
	std::fstream file_stream;
private:
	std::string file_path;
	std::string file_extension;
};

class color_space
{
	friend class pixblock;
public:
	inline pix & operator=(int new_val);
	inline pix & operator=(long new_val);
	inline pix & operator=(unsigned int new_val);
	inline pix & operator=(unsigned long new_val);

	inline operator int();
	inline operator long();
	inline operator unsigned int();
	inline operator unsigned long();

	color_space();

private:

	std::map<std::string, unsigned long> color_space_key_map;
	
	bool set_from_pixel_ref(pix * from_pixel_ptr);

	unsigned int required_bit_depth;

	std::string current_get_value;

	pix & from_pixel_ref;

};

class pix
{
	friend class color_space;
public:
	inline pix & operator=(int new_val);
	inline pix & operator=(long new_val);
	inline pix & operator=(unsigned int new_val);
	inline pix & operator=(unsigned long new_val);
	//inline pix & operator=(WORD_TYPE new_val);
	//inline pix & operator=(U_WORD_TYPE new_val);
	inline operator int();
	inline operator long();
	inline operator unsigned int();
	inline operator unsigned long();

	inline color_space & operator[](string value_string);
	//inline operator WORD_TYPE();
	//inline operator U_WORD_TYPE();
	//inline unsigned int get_bit_depth();
	pix(pixrow * from_row_ptr);

	//inline bool set_depth(unsigned int new_depth);

	
	
private:

	pixrow & from_row_ref;

	unsigned long * pixel_val;
	unsigned long bit_mask;


};

class pixrow
{
	friend class pixblock;
public:
	inline pixrow & operator=(int*);
	inline pixrow & operator=(long*);
	inline pixrow & operator=(unsigned int*);
	inline pixrow & operator=(unsigned long*);

	inline pix & operator[](unsigned int pixel_index);

	inline operator int*();
	inline operator long*();
	inline operator unsigned int*();
	inline operator unsigned long*();

	inline unsigned int length();

	pixrow(pixblock * from_block_ptr);
private:

	pixblock & from_block_ref;

	pix pixel_access_buffer;

	unsigned long * pixel_row;

};

class pixblock
{
public:
	inline operator int**();
	inline operator long**();
	inline operator unsigned int**();
	inline operator unsigned long**();

	inline operator=(int**);
	inline operator=(long**);
	inline operator=(unsigned int**);
	inline operator=(unsigned long**);

	inline pixrow & operator[](unsigned int row_index);

	inline unsigned int get_length();
	inline unsigned int get_height();

	inline bool set_height(unsigned int new_height);
	inline bool set_width(unsigned int new_width);

	inline unsigned int get_bit_depth();
	inline bool set_depth(unsigned int new_depth);

	inline bool set_color_space(std::string color_space_name_string);
	inline string get_color_space_type_name();


	pixblock();
private:

	unsigned int height;
	unsigned int width;

	unsigned int actual_height;
	unsigned int actual_width;

	unsigned int bit_depth;

	color_space * current_color_space;

	unsigned long * * pixel_block;
	pixrow pixel_row_access_buffer;
	
};

class file_stack
{

};

class image_stack
{

};

class tool
{
public:
	inline operator(std::string *);
private:
	tool_function func_from_dll;
};

class tool_map
{
public:

private:
	std::map<string, tool> tool_map;

};

class mangler
{
public:

private:

};

class mang_script_map
{

};

class codec
{

};

class codec_map
{

};

class map_populator
{

};