
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

void adb_shell(char *cmd) {
	char shell[200] = "adb shell ";
	system(strcat(shell, cmd));
}

void cd(char *root) {
	char cmd[200] = "cd ";
	adb_shell(strcat(cmd, root));
}

void file_push(char *start, char *end) {
	char push[500] = "adb push ";
	strcat(push, start);
	strcat(push, " ");
	system(strcat(push, end));
}

void file_pull(char *start, char *end) {
	char pull[500] = "adb pull ";
	strcat(pull, start);
	strcat(pull, " ");
	system(strcat(pull, end));
}

void backupf(char *file, char *target) {
	char pull[500] = "adb pull ";
	strcat(pull, file);
	strcat(pull, " ");
	strcat(pull, target);
	system(pull);
}

void get_img(char *code) {
	char cmd[200] = "wget http://cdimage.ubports.com/anbox-images/anbox-boot-";
	strcat(cmd, code);
	strcat(cmd, ".img");
	system(cmd);
}

void flash_img(char *code, char *part) {
	char cmd[200] = "fastboot flash ";
	strcat(cmd, part);
	strcat(cmd, " anbox-boot-");
	strcat(cmd, code);
	strcat(cmd, ".img");
	system(cmd);
}

void create_lib(char *id, char *name) {
	cout << "Creating Libertine Desktop " << name << ". Keep the programme running, please..." << endl;
	char create[200] = "libertine-container-manager create -i ";
	strcat(create, id);
	strcat(create, " -n ");
	strcat(create, "'");
	strcat(create, name);
	adb_shell(strcat(create, "'"));
}

void libertine(char *id, char *cmd) {
	char lib[200] = "libertine-container-manager ";
	strcat(lib, cmd);
	strcat(lib, " -i ");
	adb_shell(strcat(lib,id));
}

void inst_pkg(char *id, char *pkg_name) {
	cout << "Downloading and installing desktop dpkg " << pkg_name << ". Keep the programme running, please..." << endl;
	char lib[200] = "libertine-container-manager install-package -i ";
	strcat(lib, id);
	strcat(lib, " -p ");
	adb_shell(strcat(lib, pkg_name));
}	//Libertine 操作

void uninst_pkg(char *id, char *pkg_name) {
	cout << "Removing desktop dpkg " << pkg_name << ". Keep the programme running, please..." << endl;
	char lib[200] = "libertine-container-manager remove-package -i ";
	strcat(lib, id);
	strcat(lib, " -p ");
	adb_shell(strcat(lib, pkg_name));
}	//Libertine 操作

void lapse(double dur) {
	time_t start, end;
	start = clock();
	end = start;
	while (1) {
		if ((end - start) / CLOCKS_PER_SEC == dur) break;
		end = clock();
	}
}

void apk_inst(char *filepath) {
	char inst[500] = "adb install ";
	adb_shell(strcat(inst, filepath));
}

void mkdir(char *folder, char *backtype) {
	char dir[500] = "mkdir ";
	strcat(dir, folder);
	strcat(dir, "\\UTBackup-");
	strcat(dir, backtype);
	system(dir);
	char cur[500] = "";
	strcat(cur, folder);
	strcat(cur, "\\UTBackup-");
	strcat(cur, backtype);
	strcpy(folder, cur);
}

int main() {
	int choice;
	lapse(1);
	cout << endl << "Ubuntu Touch Management Console\n";
	lapse(1);
	cout << endl << "Made by Henry Yan (@Evergardener)" << endl << endl;
	lapse(1);
	cout << "Have you already deployed ADB on your computer?\n1. Yes.\n2. No.\n--> ";
	cin >> choice;
	if (choice == 2) {
		cout << "Sorry, please deploy ADB (Android Debug Bridge) on your computer first.\n";
		exit(0);
	}
	cout << endl << "Initializing ADB tunnel...\n\n";
	system("adb kill-server");
	system("adb start-server");
	while (1) {
		system("adb devices");
		cout << "Is your Ubuntu Touch device correctly identified?\n1. Yes.\n2. Try again.\n3. My device is in bootloader (Fastboot mode)\n--> ";
		cin >> choice;
		cin.get();
		if (choice == 1 || choice == 3) break;
		else cout << endl;
	}
	if (choice == 1) {
		lapse(1);
		cout << endl;
	}
	else if (choice == 3) {
		cout << endl << "Reboot to Ubuntu Touch?\n1. Sure\n2. Directly enter the Menu\n--> ";
		cin >> choice;
		cin.get();
		if (choice == 1) {
			cout << endl;
			system("fastboot reboot");
		}
	}
	cout << "Has Anbox been deployed on your device?\n1. Yes.\n2. No.\n--> ";
	cin >> choice;
	cin.get();
	if (choice == 1) {
		cout << "\nIs your device fully rebooted?\nPress Enter to confirm...";
		cin.get();
		cout << endl;
		adb_shell("adb devices");
		cout << "Is Anbox correctly detected? (With '********* device' displayed)\n1. Yes.\n2. No.\n--> ";
		cin >> choice;
		if (choice == 1) cout << endl << "You can deploy Anbox（Android) related options properly.\n";
		else if (choice == 2) {
			cout << endl << "Anbox is not correctly installed or initialized.\nReboot is recommended if not correctly initialized!\nReboot your device now?\n1. OK.\n2. Directly enter the menu\n--> ";
			cin >> choice;
			if (choice == 1) {
				system("fastboot reboot");
				lapse(1);
				cout << "\nIf there's any problem, you can choose to install or reinstall Anbox through the 'Install APK(s)' option.\n";
			}
			else if (choice == 2) {
				lapse(1);
				cout << "\nYou can choose to install or reinstall Anbox through the 'Install APK(s)' option.\n";
			}
		}
	}
	else {
		lapse(1);
		cout << "\nYou can choose to install or reinstall Anbox through the 'Install APK(s)' option.\n";
	}
	cout << endl;
	while (1) {
		char filepath1[200];
		char filepath2[200];
		strcpy(filepath1, "");
		strcpy(filepath2, "");
		cout << "Menu:\n1. Read storage status of your UT device\n";
		cout << "2. Copy file(s) to your device\n3. Copy file(s) from...\n4. Install APK(s) (Anbox required)\n5. Uninstall APK(s)\n6. Libertine container management\n";
		cout << "7. Export (Import) photo albums\n8. Import media file(s)\n9. Remount main storage as read-and-write\n10. Reboot to bootloader (Fastboot mode)\n11. Shutdown (Forced)\n12. Reboot (Forced)\n";
		cout << "13. Reboot and factory reset\n14. Reboot to Ubuntu Touch from bootloader (Fastboot mode)\n15. Reboot to recovery from bootloader (Fastboot mode)\n16. Flash third-party recovery in bootloader (Fastboot mode)\n17. Ubuntu Touch terminal\n18. Manually access ADB\n19. Reconnect your device\n20. Serial no. of your device\n21. Backup your device" << endl << "--> ";
		cin >> choice;
		cin.get();
		cout << endl;
		if (choice == 1) {
			adb_shell("df -H");
			cout << endl;
		}	//选项1
		else if (choice == 2) {
			cout << "Path of local file (drag to here): ";
			cin.getline(filepath1, 200);
			cout << endl;
			cout << "Path of device's target directory\n1. Main directory\n2. Documents\n3. Downloads\n4. Music\n5. Pictures\n6. Videos\n--> ";
			cin >> choice;
			cin.get();
			cout << endl;
			if (choice == 1)
				file_push(filepath1, "/home/phablet");
			else if (choice == 2)
				file_push(filepath1, "/home/phablet/Documents");
			else if (choice == 3)
				file_push(filepath1, "/home/phablet/Downloads");
			else if (choice == 4)
				file_push(filepath1, "/home/phablet/Music");
			else if (choice == 5)
				file_push(filepath1, "/home/phablet/Pictures");
			else if (choice == 6)
				file_push(filepath1, "/home/phablet/Videos");
			cout << endl;
		}	//选项2
		else if (choice == 3) {
			cout << "Path of file to be copied from your device: ";
			cin.getline(filepath2, 200);
			cout << "Path of target local directory (drag to here): ";
			cin.getline(filepath1, 200);
			file_pull(filepath2, filepath1);
			cout << endl;
		}	//选项3
		else if (choice == 4) {
			char save_path[300] = "/home/phablet/Downloads";
			char *apk_name;
			int count = 0;
			int flag;
			cout << "Already had Anbox installed on your device？\n1. Yes.\n2. Not yet.\n--> ";
			cin >> choice;
			cin.get();
			if (choice == 1) {
instapk:
				while(1) {
					cout << endl << "Local path of the APK file (Type 'exit' and enter to go back): ";
					cin.getline(filepath1, 200);
					if (strcmp(filepath1, "exit") == 0) break;
					file_push(filepath1, save_path);
					for (int i = 0; i < 500; i++) {
						if (filepath1[i] == '.' && filepath1[i + 1] == 'a' && filepath1[i + 2] == 'p' && filepath1[i + 3] == 'k') {
							for (int k = i + 3; k > 0; k--) {
								count++;
								if (filepath1[k] == '\\') {
									flag = k;
									break;
								}
							}
							break;
						}	//找到 .apk 字样
					}	//得到 apk 文件名
					apk_name = new char[count];
					apk_name[count - 1] = '\0';
					for (int i = flag + 1, k = 0, calc = 0; calc < count; calc++, i++, k++) {
						apk_name[k] = filepath1[i];
					}	//得到 apk 文件名
					cout << "Name of the pakcage: " << apk_name << endl;
					strcat(save_path, "/");
					strcat(save_path, apk_name);
					apk_inst(save_path);
				}
			}
			else if (choice == 2) {
				while (1) {
					cout << endl << "Install Anbox for Ubuntu Touch now？\n1. What is Anbox？\n2. OK.\n3. Cancel installation\n4. Install Android apps\n--> ";
					cin >> choice;
					cin.get();
					if (choice == 1) {
						cout << endl << "Anbox is an Android simulator running on Linux.\nInstalling Anbox on Ubuntu Touch just like deploying an Android simulator (virtualbox) on your device.\nThen you'll be able to install and use Android apps on Ubuntu Touch.\nIf your device was purchased from Team Forth，there's Anbox pre-installed，and no more installation is needed.\n\nPress 'Enter' to go back...";
						cin.get();
						cout << endl;
					}
					else if (choice == 2) {
						char codename[20];
						char partitionname[20];
						cout << endl << "Anbox is available on the following devices:\n1. Meizu Pro 5\n2. LG Nexus 5\n3. OnePlus One\n4. Fairphone 2\n5. BQ M10 HD\n6. BQ M10 FHD\nPlease choose your device--> ";
						cin >> choice;
						cin.get();
						if (choice == 1) {
							strcpy(codename, "turbo");
							strcpy(partitionname, "bootimg");
						}	// MEIZU
						else if (choice == 2) {
							strcpy(codename, "hammerhead");
							strcpy(partitionname, "boot");
						}	//NEXUS
						else if (choice == 3) {
							strcpy(codename, "bacon");
							strcpy(partitionname, "boot");
						}	//OPO
						else if (choice == 4) {
							strcpy(codename, "FP2");
							strcpy(partitionname, "boot");
						}	//FP2
						else if (choice == 6) {
							strcpy(codename, "frieza");
							strcpy(partitionname, "boot");
						}	//FHD
						else if (choice == 5) {
							strcpy(codename, "cooler");
							strcpy(partitionname, "boot");
						}	//HD
						cout << endl << "Entering bootloader..." << endl;
						adb_shell("sudo reboot -f bootloader");
						cout << "Dowloading Anbox image(s)..." << endl;
						get_img(codename);
						cout << "Flashing Anbox image(s)..." << endl;
						flash_img(codename, partitionname);
						cout << "Rebooting..." << endl;
						system("fastboot reboot");
						cout << "[Action acquired!]Press 'Enter' to continue after the device fully reboots...";
						cin.get();
						cout << "Remounting system storage as writable..." << endl;
						adb_shell("sudo mount -o rw,remount /");
						cout << "Upgrading source Aptitude..." << endl;
						adb_shell("sudo apt update");
						cout << "Downloading Anbox..." << endl;
						adb_shell("sudo apt install anbox-ubuntu-touch");
						cout << "Installing..." << endl;
						adb_shell("anbox-tool install");
						cout << "Installing ADB for Anbox..." << endl;
						adb_shell("sudo apt update");
						adb_shell("sudo apt install android-tools-adb");
						cout << endl;
						cout << "All done!" << endl;
						cout << endl;
						goto instapk;
					}	//安装 Anbox
					else if (choice == 3) break;
					else if (choice == 4) {
						cout << endl;
						goto instapk;
					}
				}	// 安装 Anbox 与否
			}
			cout << endl;
		}	//选项4
		else if (choice == 5) {
			char package[200];
			char uninst[500] = "adb uninstall ";
			cout << "List of APKs installed:" << endl;
			adb_shell("adb shell pm list packages");
			cout << endl << "The package name of the app to be removed (Enter 'exit' to quit removing APK(s)): ";
			cin.getline(package, 200);
			if (strcmp(package,"exit") != 0) {
				adb_shell(strcat(uninst, package));
			}
			cout << endl;
		}	//选项5
		else if (choice == 6) {
			adb_shell("sudo mount -o rw,remount /");
			char lib_id[50];
			char lib_name[50];
			cout << "Libertine container management\n\n";
			lapse(1);
			cout << "1. Create a new Libertine container\n2. Manage existing Libertine container(s)\n3. Leave Libertine container management\n--> ";
			cin >> choice;
			cin.get();
			cout << endl;
			if (choice == 1) {
				cout << "Some settings are being deployed.\nYour lockscreen (admin) password might be required!\n";
				adb_shell("sudo apt-get install python3-libertine-chroot");
				cout << "Operation complete.\n\nCreate and ID for this container (Lower case letters only): ";
				cin.getline(lib_id, 50);
				cout << "Now name your container (No special symbol): ";
				cin.getline(lib_name, 50);
				create_lib(lib_id, lib_name);
				cout << "Load complete!\nThe following Libertine container is created:" << endl;
				adb_shell("libertine-container-manager list");
				cout << endl;
				goto choice_2;
			}
			else if (choice == 2) {
			choice_2:
				while (1) {
					char  id[50];
					strcpy(id, "");
					cout << "Libertine operations:" << endl;
					cout << "1. List existing ID(s) of Libertine container(s)\n2. List installed X11 desktop dpkg(s)\n3. Download and install an X11 desktop dpkg\n4. Remove an X11 desktop dpkg\n5. Leave Libertine container management\n--> ";
					cin >> choice;
					cin.get();
					cout << endl;
					if (choice == 5) break;
					else if (choice == 1) {
						cout << "Existing Libertine container(s) including:" << endl;
						adb_shell("libertine-container-manager list");
					}	//Libertine 操作 - 1
					else if (choice == 2) {
						cout << "Enter the ID of the container you want to look up: ";
						cin.getline(id, 50);
						libertine(id, "list-apps");
					}	//Libertine 操作 - 2
					else if (choice == 3) {
						char pack_name[100];
						cout << "Enter the ID of the container you want to look up: ";
						cin.getline(id, 50);
						cout << "The name of the desktop dpkg you want to install: ";
						cin.getline(pack_name, 100);
						inst_pkg(id, pack_name);
						cout << "Installation complete!" << endl;
					}	//Libertine 操作 - 3
					else if (choice == 4) {
						char pack_name[100];
						cout << "Enter the ID of the container you want to look up: ";
						cin.getline(id, 50);
						cout << "The name of the desktop dpkg you want to remove: ";
						cin.getline(pack_name, 100);
						uninst_pkg(id, pack_name);
						cout << "Remove complete!" << endl;
					}	//Libertine 操作 - 4
					cout << endl;
				}	//Libertine 操作
			}
			cout << endl;
		}	//选项6
		else if (choice == 7) {
			cout << "You're willing to:\n1. Import image(s) or image folder(s)\n2. Export...\n--> ";
			cin >> choice;
			cin.get();
			if (choice == 2) {
				cout << "Path of target local directory (drag to here): ";
				cin.getline(filepath1, 200);
				file_pull("/home/phablet/Pictures", filepath1);
			}
			else if (choice == 1) {
				cout << "Path of the local image file or folder (drag to here): ";
				cin.getline(filepath1, 200);
				file_push(filepath1, "/home/phablet/Pictures");
			}
			cout << endl;
		}
		else if (choice == 8) {
			cout << "Path of the local video or music file or folder (drag to here): ";
			cin.getline(filepath1, 200);
			cout << "This is a:\n1. Video file (folder)\n2. Music file (folder)\n--> ";
			cin >> choice;
			cin.get();
			if (choice == 1)
				file_push(filepath1, "/home/phablet/Videos");
			else
				file_push(filepath1, "/home/phablet/Music");
			cout << endl;
		}
		else if (choice == 9) {
			cout << "Please input lockscreen (admin) password below.\n";
			adb_shell("sudo mount -o rw,remount /");
		}
		else if (choice == 10) {
			system("adb reboot bootloader");
		}
		else if (choice == 11) {
			cout << "Please input lockscreen (admin) password below.\n";
			system("adb shell sudo poweroff");
		}
		else if (choice == 12) {
			system("adb reboot");
		}
		else if (choice == 13) {
			system("adb reboot bootloader");
			system("fastboot format cache");
			system("fastboot format userdata");
			system("fastboot reboot");
		}
		else if (choice == 14) {
			system("fastboot reboot");
			cout << endl;
		}
		else if (choice == 15) {
			system("fastboot reboot recovery");
			cout << endl;
		}
		else if (choice == 16) {
			cout << "Path of the local recovery file (.img) (drag to here): ";
			cin.getline(filepath1, 200);
			cout << "Make sure your Ubuntu Touch device is in bootloader (Fastboot mode)!\n";
			char str[500] = "fastboot flash recovery ";
			system(strcat(str, filepath1));
		}
		else if (choice == 17) {
			system("adb shell");
			cout << endl;
		}
		else if (choice == 18) {
			system("adb");
			int i = 0;
			while(1) {
				char line[500];
				if (i == 0)
					cout << endl << "Enter ADB command: ";
				else cout << "Enter ADB command (Enter 'exit' to quit ADB): ";
				cin.getline(line, 500);
				if (!strcmp(line, "exit")) break;
				else if (!strcmp(line, "adb")) cout << endl;
				system(line);
				i++;
			}
			cout << endl;
		}
		else if (choice == 19) {
			system("adb reconnect");
			system("adb devices");
		}
		else if (choice == 20) {
			system("adb get-serialno");
			cout << endl;
		}
		else if (choice == 21) {
			cout << "Local directory where the backup files are stored (drag to here): ";
			cin.getline(filepath1, 200);
			cout << "Is Anbox deployed on your device?\n1. Yes\n2. No\n--> ";
			cin >> choice;
			cin.get();
			if (choice == 1) {
				cout << endl << "We can help you backup Anbox data, but if you are resetting your device, Anbox should be re-installed after the reset!\n";
			}
			cout << endl << "Choose to backup:\n1. All data\n2. All media (music/videos/images)\n3. Downloads\n4. Documents\n--> ";
			cin >> choice;
			cin.get();
			cout << endl;
			if (choice == 1) {
				mkdir(filepath1, "all");
				backupf("/home/phablet/anbox-data", filepath1);
				backupf("/home/phablet/Desktop", filepath1);
				backupf("/home/phablet/Documents", filepath1);
				backupf("/home/phablet/Downloads", filepath1);
				backupf("/home/phablet/Music", filepath1);
				backupf("/home/phablet/Pictures", filepath1);
				backupf("/home/phablet/Public", filepath1);
				backupf("/home/phablet/Templates", filepath1);
				backupf("/home/phablet/Videos", filepath1);
			}	//备份全部资料
			else if (choice == 2) {
				mkdir(filepath1, "media");
				backupf("/home/phablet/Music", filepath1);
				backupf("/home/phablet/Pictures", filepath1);
				backupf("/home/phablet/Videos", filepath1);
			}	//所有多媒体数据
			else if (choice == 3) {
				mkdir(filepath1, "downs");
				backupf("/home/phablet/Downloads", filepath1);
			}	//备份下载内容
			else if (choice == 4) {
				mkdir(filepath1, "docs");
				backupf("/home/phablet/Documents", filepath1);
			}	//备份文档
			cout << endl << "Backup finished!" << endl << endl;
		}
	}	//功能列表循环
}
