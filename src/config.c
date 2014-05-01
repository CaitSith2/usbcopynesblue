#include "StdAfx.h"
#include <shlobj.h>

int	HWVer;
int	ParPort, ParAddr, ParECP;
BOOL	SaveCRC, SaveFiles, MakeUnif;
char	Path_MAIN[MAX_PATH], Path_PRG[MAX_PATH], Path_CHR[MAX_PATH], Path_WRAM[MAX_PATH],
	Path_NES[MAX_PATH], Path_CRC[MAX_PATH], Path_NSF[MAX_PATH], Path_PLUG[MAX_PATH];

/* Note: base path must have a trailing backslash */
char *	_relpath (char *abspath, char *basepath)
{
	int i, j, k;
	char tmp[MAX_PATH];
	tmp[0] = 0;
	i = 0;
	
	while ((tolower(abspath[i]) == tolower(basepath[i])) && (basepath[i] != 0))
		i++;
	if (basepath[i])
	{
		k = 1;
		for (j = i; basepath[j] != 0; j++)
			if (basepath[j] == '\\')
				k++;
		for (j = 1; j < k; j++)
			strcat(tmp,"..\\");
	}
	strcat(tmp,&abspath[i]);
	if (strlen(tmp) == 0)
		strcpy(tmp,".");
	strcpy(abspath,tmp);
	return abspath;
}
char *	addSlash (char *path)
{
	int x = strlen(path);
	if (path[x-1] == '\\')
		return path;
	path[x] = '\\';
	path[x+1] = 0;
	return path;
}

void	GetProgPath (void)
{
	int i;
	GetModuleFileName(NULL,Path_MAIN,MAX_PATH);
	i = strlen(Path_MAIN);
	while (i > 0)
		if (Path_MAIN[--i] == '\\')
		{
			Path_MAIN[++i] = 0;
			return;
		}
}

void	GetConfig (void)
{
	char Config[MAX_PATH], tmpdir[MAX_PATH], tmpstr[16];
	strcpy(Config,Path_MAIN);
	strcat(Config,"USB CopyNES.ini");
	SaveCRC = GetPrivateProfileInt("USB CopyNES","SaveCRC",0,Config);
	SaveFiles = GetPrivateProfileInt("USB CopyNES","SaveFiles",0,Config);
	MakeUnif = GetPrivateProfileInt("USB CopyNES","MakeUnif",0,Config);
	GetPrivateProfileString("USB CopyNES","PRGPath","Parts",Path_PRG,MAX_PATH,Config);
	GetPrivateProfileString("USB CopyNES","CHRPath","Parts",Path_CHR,MAX_PATH,Config);
	GetPrivateProfileString("USB CopyNES","WRAMPath","Finished",Path_WRAM,MAX_PATH,Config);
	GetPrivateProfileString("USB CopyNES","NESPath","Finished",Path_NES,MAX_PATH,Config);
	GetPrivateProfileString("USB CopyNES","CRCPath","CRC",Path_CRC,MAX_PATH,Config);
	GetPrivateProfileString("USB CopyNES","NSFPath","NSF",Path_NSF,MAX_PATH,Config);
	GetPrivateProfileString("USB CopyNES","PluginPath","Plugdone",Path_PLUG,MAX_PATH,Config);
	strcpy(Path_PRG,addSlash(_fullpath(strcpy(tmpdir,Path_MAIN),Path_PRG,MAX_PATH)));
	strcpy(Path_CHR,addSlash(_fullpath(strcpy(tmpdir,Path_MAIN),Path_CHR,MAX_PATH)));
	strcpy(Path_WRAM,addSlash(_fullpath(strcpy(tmpdir,Path_MAIN),Path_WRAM,MAX_PATH)));
	strcpy(Path_NES,addSlash(_fullpath(strcpy(tmpdir,Path_MAIN),Path_NES,MAX_PATH)));
	strcpy(Path_CRC,addSlash(_fullpath(strcpy(tmpdir,Path_MAIN),Path_CRC,MAX_PATH)));
	strcpy(Path_NSF,addSlash(_fullpath(strcpy(tmpdir,Path_MAIN),Path_NSF,MAX_PATH)));
	strcpy(Path_PLUG,addSlash(_fullpath(strcpy(tmpdir,Path_MAIN),Path_PLUG,MAX_PATH)));
	ParPort = GetPrivateProfileInt("USB CopyNES","ParPort",0,Config);
	GetPrivateProfileString("USB CopyNES","ParAddr","0",tmpstr,16,Config);
	sscanf(tmpstr,"%X",&ParAddr);
	GetPrivateProfileString("USB CopyNES","ParECP","0",tmpstr,16,Config);
	sscanf(tmpstr,"%X",&ParECP);
	if ((ParPort > 0) && (ParAddr == 0))
	{
		// update old config data
		if (ParPort == 1)
			ParAddr = 0x378;
		if (ParPort == 2)
			ParAddr = 0x278;
		if (ParPort == 3)
			ParAddr = 0x3BC;
		if ((ParPort == 4) || (ParPort == 9))
			ParAddr = 0xD800;
		if (ParPort == 5)
			ParAddr = 0xE000;
		if (ParPort == 6)
			ParAddr = 0xE800;
		if (ParPort > 4)
			ParPort = 4;
		WriteConfig();
	}
	if ((ParAddr > 0) && (ParECP == 0))
	{
		ParECP = 0x400;
		WriteConfig();
	}
}
void	WriteConfig (void)
{
	char Config[MAX_PATH], tmpdir[MAX_PATH], tmpstr[16];
	strcpy(Config,Path_MAIN);
	strcat(Config,"USB CopyNES.ini");
	sprintf(tmpstr,"%i",SaveCRC);
	WritePrivateProfileString("USB CopyNES","SaveCRC",tmpstr,Config);
	sprintf(tmpstr,"%i",SaveFiles);
	WritePrivateProfileString("USB CopyNES","SaveFiles",tmpstr,Config);
	sprintf(tmpstr,"%i",MakeUnif);
	WritePrivateProfileString("USB CopyNES","MakeUnif",tmpstr,Config);
 	WritePrivateProfileString("USB CopyNES","PRGPath",_relpath(strcpy(tmpdir,Path_PRG),Path_MAIN),Config);
	WritePrivateProfileString("USB CopyNES","CHRPath",_relpath(strcpy(tmpdir,Path_CHR),Path_MAIN),Config);
	WritePrivateProfileString("USB CopyNES","WRAMPath",_relpath(strcpy(tmpdir,Path_WRAM),Path_MAIN),Config);
	WritePrivateProfileString("USB CopyNES","NESPath",_relpath(strcpy(tmpdir,Path_NES),Path_MAIN),Config);
	WritePrivateProfileString("USB CopyNES","CRCPath",_relpath(strcpy(tmpdir,Path_CRC),Path_MAIN),Config);
	WritePrivateProfileString("USB CopyNES","NSFPath",_relpath(strcpy(tmpdir,Path_NSF),Path_MAIN),Config);
	WritePrivateProfileString("USB CopyNES","PluginPath",_relpath(strcpy(tmpdir,Path_PLUG),Path_MAIN),Config);
	sprintf(tmpstr,"%i",ParPort);
	WritePrivateProfileString("USB CopyNES","ParPort",tmpstr,Config);
	sprintf(tmpstr,"%X",ParAddr);
	WritePrivateProfileString("USB CopyNES","ParAddr",tmpstr,Config);
	sprintf(tmpstr,"%X",ParECP);
	WritePrivateProfileString("USB CopyNES","ParECP",tmpstr,Config);
}

int	FindVersion (void)
{
	BYTE i;
    OpenStatus(topHWnd);
	StatusText("Querying CopyNES BIOS version...");
	if (!WriteByteEx(0xA2,3,FALSE))
	{
		StatusText("Failed to send version request!");
		StatusText("Make sure your CopyNES is plugged in and turned on!");
		StatusOK();
		return 0;	// write failed, device not present
	}
	StatusText("Waiting for reply...");
	if (!ReadByteEx(&i,3,FALSE))
	{
		if (ParPort == -1)
		{
			StatusText("Version reply not received!");
		    StatusText("Make sure your CopyNES is plugged in and turned on!");
			StatusOK();
			return 0;	// write failed, device not present
		}
		else
		{
			StatusText("Version reply not received! Assuming version 1 BIOS.");
			Sleep(SLEEP_LONG);
			CloseStatus();
			InitPort();
			ResetNES(RESET_COPYMODE);
			return 1;
		}
	}
	if ((i == 0xA2) && (ParPort != -1))
	{
		StatusText("Your parallel port does not support bidirectional communication!");
		StatusText("Please correct your BIOS settings and try again.");
		StatusOK();
		return 0;	// read failed, device not present
	}
	StatusText("CopyNES identified as version %i.",i);
	Sleep(SLEEP_LONG);
	CloseStatus();
	// technically, these shouldn't be needed
	if (ParPort != -1)
		InitPort();
	ResetNES(RESET_COPYMODE);
	return i;
}

PCategory *Plugins = NULL;
int numcats = 0;

static	void	trim (char *str)
{
	int i;
	for (i = strlen(str) - 1; i >= 0; i--)
	{
		if (str[i] == ' ')
			str[i] = 0;
		else	break;
	}
}

BOOL MakeCategory(char *description, int type)
{
	numcats++;
	Plugins = realloc(Plugins, (numcats+1) * sizeof(PCategory));	// allocate another slot
	memset(&Plugins[numcats], 0, sizeof(PCategory));		// clear the new one at the end
	
	Plugins[numcats-1] = (PCategory)malloc(sizeof(TCategory));
	Plugins[numcats-1]->listlen = 0;
	Plugins[numcats-1]->list = (PPlugin *)malloc(sizeof(PPlugin));
	memset(Plugins[numcats-1]->list, 0, sizeof(PPlugin));
	Plugins[numcats-1]->type = type;
	Plugins[numcats-1]->desc = strdup(description);
	
	return TRUE;
}



BOOL MakePlugin(int category, char *name, char *file, char *nsffile, int number, char *description)
{
	FILE *PLUGIN;
	TPlugin *plugin;

	char filename[MAX_PATH];
	strcpy(filename,Path_PLUG);
	strcat(filename,file);

	plugin = (TPlugin*)malloc(sizeof(TPlugin));
	if(plugin == NULL)
		return FALSE;
	
	if(number != 9998)
	{
		if ((PLUGIN = fopen(filename,"rb")) == NULL)
		{
			if(nsffile == NULL)
			{
				free(plugin);
				return FALSE;
			}
			strcpy(filename,Path_PLUG);
			strcat(filename,nsffile);
			if ((PLUGIN = fopen(filename,"rb")) == NULL)
			{
				free(plugin);
				return FALSE;
			}
			else
			{
				fclose(PLUGIN);
				plugin->file = strdup(nsffile);
			}
		}
		else
		{
			plugin->file = strdup(file);
			fclose(PLUGIN);
		}
	}
	else
		plugin->file = strdup("xxxx.bin");

	plugin->name = strdup(name);
	if(nsffile != NULL)
	{
		strcpy(filename,Path_PLUG);
		strcat(filename,nsffile);
		if((PLUGIN = fopen(filename,"rb")) == NULL)
			plugin->nsffile = NULL;
		else
		{
			plugin->nsffile = strdup(nsffile);
			fclose(PLUGIN);
		}
	}
	else
		plugin->nsffile = NULL;
	plugin->num = number;
	plugin->desc = strdup(description);

	Plugins[category]->listlen++;
	Plugins[category]->list = realloc(Plugins[category]->list, (Plugins[category]->listlen+1) * sizeof(TPlugin));
	Plugins[category]->list[Plugins[category]->listlen-1] = plugin;
	memset(&Plugins[category]->list[Plugins[category]->listlen], 0, sizeof(PPlugin));

	return TRUE;
}

BOOL	Startup	(void)
{
	char mapfile[MAX_PATH];
	FILE *PlugList;
	char *Data, *C1, *C2, *C3, *C4;
	int i, j;

	int col0, col1, col2, col3, col4;


	InitCRC();
	GetProgPath();
	GetConfig();

	sprintf(mapfile,"%s%s",Path_MAIN, "mappers.dat");
	PlugList = fopen(mapfile, "rt");
	if (PlugList == NULL)
	{
		MessageBox(topHWnd,"Unable to open mappers.dat plugin list!", "USB CopyNES", MB_OK | MB_ICONERROR);
		return FALSE;
	}
	// step 1 - Read the column information
	fscanf(PlugList,"%i %i %i %i %i\n", &col0, &col1, &col2, &col3, &col4);
	col0--; col1--; col2--; col3--; col4--;
	C1 = malloc(col1 - col0 + 1);	C1[col1 - col0] = 0;
	C2 = malloc(col2 - col1 + 1);	C2[col2 - col1] = 0;
	C3 = malloc(col3 - col2 + 1);	C3[col3 - col2] = 0;
	C4 = malloc(col4 - col3 + 1);	C4[col4 - col3] = 0;
	Data = malloc(col4);

	Plugins = malloc(sizeof(PCategory));
	memset(Plugins, 0, sizeof(PCategory));

	// step 2 - read in the list
	while (!feof(PlugList))
	{
		fscanf(PlugList,"%[^\n]\n",Data);
		memcpy(C1,Data + col0, col1 - col0);
		memcpy(C2,Data + col1, col2 - col1);
		memcpy(C3,Data + col2, col3 - col2);
		memcpy(C4,Data + col3, col4 - col3);
		trim(C1);
		trim(C2);
		trim(C3);
		trim(C4);
		if(!strncmp(C1,"****",4))
			continue;	//Comment line, the rest of it should be ignored.
		if (!strcmp(C1,"*"))
		{
			if (!strcmp(C4,"end"))
				break;
			MakeCategory(C4,atoi(C3));
		}
		else
		{
			MakePlugin(numcats-1,C1,C2,NULL,atoi(C3),C4);
		}
	}

	fclose(PlugList);
	free(C1);
	free(C2);
	free(C3);
	free(C4);
	free(Data);

	// RAMCART - create new category for upload plugins
	MakeCategory("RAM/Flash cartridge programmer",PLUG_UPLOAD);
	MakePlugin(numcats-1,	"NRAM",					"ram.bin",		"ram.bin",			0,	"NROM cart with 32K PRG RAM and 8K CHR RAM");
	MakePlugin(numcats-1,	"CNRAM",				"cnram.bin",	"cnram.bin",		1,	"CNROM cart with 32K PRG RAM and 32KB CHR RAM");
	MakePlugin(numcats-1,	"UfROM",				"uxram.bin",	"uxram.bin",		2,	"Membler's flash cart for UNROM");
	MakePlugin(numcats-1,	"PowerPak Lite",		"pplite.bin",	"pplite.bin",		3,	"PowerPak Lite RAM Cart Loader");
	MakePlugin(numcats-1,	"PowerPak Boot",		"pp.bin",		NULL,				4,	"PowerPak Boot Flasher");
	MakePlugin(numcats-1,	"Glider Flasher",		"glider.bin",	"glidernsf.bin",	5,	"Glider House Flasher");
	MakePlugin(numcats-1,	"URROM512 Flasher",		"unrom512.bin",	"unrom512nsf.bin",	6,	"Sealie Computing UNROM512 Flasher");
	// END RAMCART

	if (!OpenPort(ParPort, ParAddr, ParECP))
	{
		HWVer = 0;
		return TRUE;
	}
	if (ParPort != -1)
		InitPort();
	ResetNES(RESET_COPYMODE);
	Sleep(SLEEP_LONG);
	ResetNES(RESET_COPYMODE);
	HWVer = FindVersion();
	return TRUE;
}

void	Shutdown (void)
{
	int i, j;
	
	WriteConfig();
	
	if (Plugins)
	{
		for (i = 0; i < numcats; i++)
		{
			for (j = 0; j < Plugins[i]->listlen; j++)
			{
				if(Plugins[i]->list[j]->desc) free(Plugins[i]->list[j]->desc);
				if(Plugins[i]->list[j]->file) free(Plugins[i]->list[j]->file);
				if(Plugins[i]->list[j]->nsffile) free(Plugins[i]->list[j]->nsffile);
				if(Plugins[i]->list[j]->name) free(Plugins[i]->list[j]->name);
				if(Plugins[i]->list[j]) free(Plugins[i]->list[j]);
			}
			free(Plugins[i]->desc);
			free(Plugins[i]);
		}
		free(Plugins);
	}
    ResetNES(RESET_PLAYMODE);
	ClosePort();
}
