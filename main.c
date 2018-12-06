/* * * * *
 * Название: ri - команда запуска имитатора(ов)
 * Версия: 0.2.1
 * Описание: производит запуск окружения и самого имитатора
 * Программист разработчик: Дарьин М.В.
 * Программист сопровождения:
 * Дата создания: 17.12.2012
 * Дата последнего изменения: 07.04.2013
 * Организация: ЗАО "ОКБ "ИКАР"
 * Лицензия: "AS-IS" "NO WARRENTY"
 * Контакты:
 * почта: 
 * адрес: 
 * 
 * 2012
 * 
 * * */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

//__DEBUG 
// если определён, то отладочный режим = ВКЛ
#define DEBUG 1
//иначе отладочный режим = ВЫКЛ
//#undef DEBUG
/*
"\n in the future...\n"\ 
"--complex=<complex> --imitators <imitator1> <imitator2> ... <imitatorN> --uid=<uid> --profile=<profile>\n"\
*/
#define get_vsn() ("0.2.0")
#define get_usage() ("Usage: ri [OPTIONS] COMPLEX IMITATOR UID PROFILE\n"\
"\n"\
"Run IMITATOR(s)"\
"\n"\
"  -c | --complex\n"\
"  -v | --version\n"\
"  -h | --help")

// пути для размещения сгенерированных файлов
#define get_project_root_dir() ("C:\\Project\\ikar2")
#define get_ipanels_dir() ("C:\\Project\\ikar2\\ipanels")
#define get_wrappers_dir() ("C:\\Project\\ikar2\\wrapper")
#define get_virtual_wrappers_dir() ("C:\\Project\\ikar2\\wrappers\\virtual")
#define get_icfg_dir() ("C:\\Project\\ikar2\\icfg")
#define get_complexes_dir() ("C:\\Project\\ikar2\\icfg\\complexes")
#define get_profile_dir() ("C:\\Project\\ikar2\\icfg\\profile")
#define get_scripts_dir() ("C:\\Project\\ikar2\\scripts")
#define get_bin_dir() ("c:\\project\\ikar2\\bin\\")

/* direct.h
int chdir(char* path)
int chdrive(int drive)
char* getcwd(char* buffer, size_t length)
int getdrive(void)
int mkdir(const char* pathname)
int rmdir(const char* pathname)
void fnmerge(char* path, const char* drive, const char* dir, const char* name, const char* ext)
int fnsplit(const char* path, char* drive, char* dir, char* name, char* ext)
char* searchpath(const char* file)
*/

/*
 echo All.bat started
rem All.bat индекс_комплекса индекс_имитатора параметр
rem 	параметр - р: запускает следуюший пакетный фаил после нажатия any key
rem		 - np: запускает следуюший пакетный фаил без ожидания нажатия any key
rem пример: All.bat 15ktest nnn np
rem	    All.bat 15k660 15k660_02 p

rem о изменениях фаила просьба сообщать
rem									Rezus666

rem фаил изменён: добавлена возможность запуска 2-х имитаторов

rem команды теперь выглядят  так:
rem All.bat параметр1 индекс_комплекса индекс_имитатора1 параметр2 индекс_имитатора2  
rem 	параметр1 - р: запускает следуюший пакетный фаил после нажатия any key
rem		  - np: запускает следуюший пакетный фаил без ожидания нажатия any key
rem	параметр2 - количество запускаемых форм (пока 1 или 2)
rem пример: All.bat np 15ktest nnn 
rem	    All.bat p 15k660 15k660_02 1
rem	    All.bat p 15k660 15k660_02 2 nnn
rem	    All.bat np 15k660 15k660_01_07 2 15k660_02

rem требуться тестирование
rem									Rezus666
 pushd ..\bin

start run_evdisp.bat %2 %6

if /i %1 == p pause
popd
pushd ..\bin

start run_iic.bat %2 %6

if /i %1 == p pause
popd

start run_logic.bat %2  %3 %6 -debug 

if /i %1 == p pause

start run_imitator.bat %2  %3 0 %6



if /i %1 == p pause

if /i %4 == 2 start run_logic.bat %2  %5 %6 -debug

if /i %1 == p pause

if /i %4 == 2 start run_imitator.bat %2  %5 0 %6


echo All.bat stopped
 
 */

char *ProjectRoot = NULL;
char IpanelsDir[256] = {0};
char WrappersVirtualDir[256] = {0};
char IcfgDir[256] = {0};
char ProfileDir[256] = {0};
char ScriptsDir[256] = {0};
char BinDir[256] = {0};
char TemplatesDir[256] = {0};

/* *
 * -------------------------------------------------------
 * Function:
 * Input:
 * Output:
 * Description:
 */
void initialize_dirstruct(void)
{
  strcpy(IpanelsDir, ProjectRoot);
  strcat(IpanelsDir, "\\ipanels");

  strcpy(IcfgDir, ProjectRoot);
  strcat(IcfgDir, "\\icfg");

  strcpy(ProfileDir, IcfgDir);
  strcat(ProfileDir, "\\profile");

  strcpy(WrappersVirtualDir, ProjectRoot);
  strcat(WrappersVirtualDir, "\\wrappers\\virtual");

  strcpy(ScriptsDir, ProjectRoot);
  strcat(ScriptsDir, "\\scripts");

  strcpy(BinDir, ProjectRoot);
  strcat(BinDir, "\\bin");

  strcpy(TemplatesDir, ProjectRoot);
  strcat(TemplatesDir, "\\utils\\ci\\templates");

  printf("ipanels: %s\nicfg: %s\nprofile: %s\nvirtual: %s\nscripts: %s\nbin: %s\n", IpanelsDir, IcfgDir, ProfileDir, WrappersVirtualDir, ScriptsDir, BinDir);

  return;
}


/* *
 * -------------------------------------------------------
 * Function:
 * Input:
 * Output:
 * Description:
 */
void run(int argc, char **argv)
{
    char FullPath[256] = {0};
    char Imitator[256] = {0};
    char Complex[256] = {0};
    char Uid[256] = {0};
    char Profile[256] = {0};
    char Cmd[256] = {0};
    char File[256] = {0};
    
    int device = 2;
	// исключить название уида и профиля
    int	ndevices = argc - 3;
	// генерировать имитаторы пока не закончится список
	char **ImitatorsList = argv;
	chdir(BinDir);
  strcpy(Cmd, "start run_evdisp ");
  strcat(Cmd, argv[1]);
  strcat(Cmd, " ");
  strcat(Cmd, argv[argc-1]);
  system(Cmd);

	do {
	  //chdir(BinDir);
    //  strcpy(Cmd, "start run_evdisp ");
    //  strcat(Cmd, argv[1]);
    //  strcat(Cmd, " ");
    //  strcat(Cmd, argv[argc-1]);
    //  system(Cmd);
    
      strcpy(Cmd, "start run_iic ");
      strcat(Cmd, argv[1]);
      strcat(Cmd, " ");
      strcat(Cmd, argv[argc-1]);
      system(Cmd);
    
      strcpy(Cmd, "start run_ilogger ");
      strcat(Cmd, argv[1]);
      strcat(Cmd, " ");
      strcat(Cmd, argv[argc-1]);
      system(Cmd);
    
      strcpy(Cmd, "start run_logic ");
      strcat(Cmd, argv[1]);
      strcat(Cmd, " ");
      strcat(Cmd, argv[device]);
      strcat(Cmd, " ");
      strcat(Cmd, argv[argc-1]);
      strcat(Cmd, " -debug");
      system(Cmd);
    
      strcpy(Cmd, "start run_imitator ");
      strcat(Cmd, argv[1]);
      strcat(Cmd, " ");
      strcat(Cmd, argv[device]);
      strcat(Cmd, " ");
      strcat(Cmd, argv[argc-2]);
      strcat(Cmd, " ");
      strcat(Cmd, argv[argc-1]);
      system(Cmd);
      fprintf(stdout, "\nImitator: %s started   [ ok ]\n", Imitator);
	  printf("::%s\n", argv[device]); 		
	} while (device++ < ndevices); 
    	
  return;
}


/* *
 * -------------------------------------------------------
 * Function:
 * Input:
 * Output:
 * Description:
 */
int main(int argc, char **argv)
{
  int Status = 0;
  FILE *Stream = stdout;
  #ifdef DEBUG
  printf("argc: %d\n", argc);
  #endif
  /*
  char FullPath[256] = {0};
  char Imitator[256] = {0};
  char Complex[256] = {0};
  char Uid[256] = {0};
  char Profile[256] = {0};
  char Cmd[256] = {0};
  char File[256] = {0};
  */
  //char *Qmake = "C:\\Qt\\4.6.2\\bin";
  //char *PATH = getenv("Path");
  //strcat(PATH, Qmake);
  //setenv("Path", PATH, 1);
  ProjectRoot = getenv("IKAR_ROOT");
  if (NULL == ProjectRoot) {
    printf("%s:Can't find IKAR_ROOT env variable, please setup and try again.\n", argv[0]);
    exit(0);
  }
  printf("IKAR_ROOT: [%s]\n", ProjectRoot);
  initialize_dirstruct();
  int device;
  int ndevices;
  char **ImitatorsList = NULL;
  switch(argc) {
  case 0:
  case 1:
    printf("\nrun imitator v.%s\n\n%s", get_vsn(), get_usage());
    break;
  case 5:
    /*  
     порядок запуска приложений может быть любым, 
     но рекомендуемый: evdisp, iic, ilogger, logic, imitator 
     [http://trac.ikar.net/projects/ikar2/wiki/%D0%97%D0%B0%D0%BF%D1%83%D1%81%D0%BA]
     
     complex=15k777 imitator1=15k777_1 imitator2=15k777_2 imitator3=15k777_3 profile=prf_777 
       
     All.bat np 15k777 15k777_1 prf_777
     
     run_evdisp.bat 
     run_iic.bat
     run_logic.bat
     run_imitator.bat
     run_ilogger  
     
     run_evdisp 15ktest
	 run_iicdispatcher 15ktest -noprofile 
	    повидимому заменён на run_iic
	 run_ilogger 15ktest
	 run_logic 15ktest nnn
	 run_imitator 15ktest nnn 0 -noprofile -plugin 
     [http://trac.ikar.net/projects/ikar2/wiki/%D0%97%D0%B0%D0%BF%D1%83%D1%81%D0%BA]
     */
    //strcpy(Imitator, argv[1]);
    
    #ifdef DEBUG
    fprintf(stdout, "complex: %s\nimitator: %s\nuid: %s\nprofile: %s\n", 
					argv[1],
					argv[2],
					argv[3],
					argv[4]);
    #endif
    
    run(argc, argv); 
    break; 
  default:      		
    // пропустить название комплекса
    run(argc, argv);
    break;  
  } // eof switch
  return Status;
} // eof main

