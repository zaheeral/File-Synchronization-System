#include <stdio.h>
// Add your system includes here.
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "ftree.h"
#include "hash.h"

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <libgen.h>

char * pathway_concat(const char * str1, const char * str2){
	char * new_path = malloc(strlen(str1) + strlen(str2) + 20);
	strcpy(new_path, str1);
	strcat(new_path, "/");
	strcat(new_path, str2);
	if (new_path == NULL) {
		perror(new_path);
	}
	return new_path;
}






int file_empty(int count){
	if(count == 1 || count == 2){
		return -1;
	}else if(count == 2){
		return 0;
	}else{
		return count;
	}
	return count;
}

int file_entries_dic(char * filepath){
	int count = 0;
	struct dirent *file_dict_inf;	
	DIR *file_dict;
	file_dict = opendir(filepath);
	while ((file_dict_inf = readdir(file_dict)) != NULL){
		count += 1;
	}
	file_empty(count);
	close(file_dict);
	return file_empty(count);;
}




void root_copy(char *src, char * path_to_destin){
	struct stat file;
	FILE *source_of_file; 
	FILE *source_of_desti; 
	char data[1];
	if(lstat(src, &file) == -1){
		perror("File read error\n");
		return -1;
	}
	if (S_ISDIR(file.st_mode))
	{
		printf("Making first folder at path_to_destin: %s\n", path_to_destin);
		if(mkdir(path_to_destin, file.st_mode & 0777) == -1){
			perror("Root directory not made\n");
		}
	}else if(S_ISREG(file.st_mode))

	{
		source_of_desti = fopen(path_to_destin, "wb");
		source_of_file = fopen(src, "rb");
		if(source_of_desti == NULL){
			perror("Dest file not opening\n");
		}
		if(source_of_file == NULL){
			perror("Src file not opening\n");
		}
		while(fread(data, 1, 1, source_of_file) != 0){
			fwrite(data, 1, strlen(data), source_of_desti);
		}
	}
}




int copy_ftree(const char *src, const char *dest){
	int count = 1;
	int i;
	char * path_to_source; 
	FILE *source_of_file; 
	char * new_path_desti; 
	DIR *dir_of_source; 
	char * path_to_destin;
	pid_t child_stats;
	char data[1];
	DIR *dir_of_destin; 
	struct dirent *source_info;	
	struct stat file;
	int child;
	int mkdir_valz;
	char *source_hash;
	char *destination_hash;
	char * new_path_sourc;
	FILE *source_of_desti; 
	pid_t highest_pid = getpid();
	char fake_string[64]; 
	int z_20_algrotithm = 0; 
	dir_of_source = opendir(src);
	if(dir_of_source==NULL) {
    	perror("root directory does not open\n");
  	}
	path_to_destin = pathway_concat(dest, basename(src));
	printf("path_to_destin assigned: %s\n", path_to_destin);
	root_copy(src, path_to_destin);
	child = fork();
	path_to_source = src; 
	if(child == 0){
		while((source_info = readdir(dir_of_source)) != NULL){
			if(source_info->d_name[0] != '.'){
				new_path_sourc = pathway_concat(path_to_source, source_info->d_name);
				lstat(new_path_sourc, &file);
				new_path_desti = pathway_concat(path_to_destin, source_info->d_name);
				if (S_ISREG(file.st_mode))
				{
					source_of_file = fopen(new_path_sourc, "r");
					if(source_of_file == NULL){
					}
					z_20_algrotithm = 0;
					source_of_desti = fopen(new_path_desti, "r");
					if(source_of_desti == NULL){
						printf("Creating new file\n");
						source_of_desti = fopen(new_path_desti, "w");
						z_20_algrotithm = 1;
					}else{
						printf("Hashing src...\n");
						for(i=0; i<=64; i++){
							source_hash[i] = fake_string[i];
						}
						source_hash = hash(source_of_file);
						printf("Hashing dest...\n");
						destination_hash = hash(source_of_desti);
						printf("Hash data:\nsrc: \n");
						show_hash(source_hash, 64);
						printf("dest: \n");
						show_hash(destination_hash, 64);
						printf("Check hash: %d, %d, %d\n", check_hash(source_hash, destination_hash, 64), sizeof(source_hash), sizeof(destination_hash));
						z_20_algrotithm = (check_hash(source_hash, destination_hash, 64) != 64);
					}
					if(z_20_algrotithm){
						source_of_file = fopen(new_path_sourc, "rb");
						source_of_desti = fopen(new_path_desti, "wb");

						rewind(source_of_file);
						rewind(source_of_desti);
						while(fread(data, 1, 1, source_of_file) != 0){
							fwrite(data, 1, strlen(data), source_of_desti);
						}
					}
					if(source_of_desti != NULL){
						chmod(new_path_desti, file.st_mode & 0777);
					}
					fclose(source_of_file);
					fclose(source_of_desti);
				}else if (S_ISDIR(file.st_mode))
				{
					dir_of_destin = opendir(new_path_desti);
					if(dir_of_destin){
						chmod(new_path_desti, file.st_mode & 0777);
					}
					else if(ENOENT == errno){
						mkdir_valz = mkdir(new_path_desti, file.st_mode & 0777);
					}
					closedir(dir_of_destin);
					if(file_entries_dic(new_path_sourc) > 0){
						child = fork();
					}
					if(child == 0 && file_entries_dic(new_path_sourc) > 0){
						path_to_source = new_path_sourc;
						path_to_destin = new_path_desti;
						dir_of_source = opendir(path_to_source);
					}
				}
			}
		}
	}
}