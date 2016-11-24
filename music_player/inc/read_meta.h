#ifndef READ_META_H
#define READ_META_H

#ifdef __cplusplus
	extern "C" {
#endif


/*************************************************************************************************************************************
*   D E F I N E S
*************************************************************************************************************************************/
#define FILENAME	0
#define ARTIST		1
#define TITLE		2
#define DATABASE_MAX_LINE_SIZE 256
#define COLUMBS		3


/*************************************************************************************************************************************
*   S T R U C U T R E
*************************************************************************************************************************************/
struct meta { char ***meta_array; int rows; };


/*************************************************************************************************************************************
*   P R O T O T Y P E S
*************************************************************************************************************************************/
void meta_init(const char *database_path, struct meta *smeta);
void add_metainfo(struct meta *pmeta, const char *column1, const char *column2, const char *column3);
void read_metinfo_from_file(const char *file_path, struct meta *pmeta);
void sort_meta(struct meta *pmeta, int sort_type);
void swap_entry(struct meta *pmeta, int row);


#ifdef __cplusplus
        }
#endif
#endif
