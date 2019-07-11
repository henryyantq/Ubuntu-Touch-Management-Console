#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <ctime>
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

void lapse(double dur) {
	time_t start, end;
	start = clock();
	end = start;
	while(1) {
		if ((end - start)/CLOCKS_PER_SEC == dur) break;
		end = clock();
	}
}

void apk_inst(char *filepath) {
	char inst[500] = "adb install ";
	adb_shell(strcat(inst, filepath));
}

int main() {
	int choice;
	lapse(1);
	cout << endl << "Ubuntu Touch �豸���� (Mac OS X)\n";
	lapse(1);
	cout << endl << "�� Henry Yan (@Evergardener) ����" << endl << endl;
	lapse(1);
	cout << "�����豸�Ƿ�װ�� adb �ļ���\n1���ǵ�\n2������Ϊ�Ұ�װ\n--> ";
	cin >> choice;
	if (choice == 2)
		system("brew cask install android-platform-tools");
	cout << endl << "���ڳ�ʼ�� ADB �����...\n\n";
	system("adb kill-server");
	system("adb start-server");
	while (1) {
		system("adb devices");
		cout << "���� Ubuntu Touch �豸�Ƿ�ʶ����ȷ��\n1���ǵ�\n2������һ��\n--> ";
		cin >> choice;
		if (choice == 1) break;
		else cout << endl;
	}
	lapse(1);
	cout << endl;
	while(1) {
		char filepath1[200];
		char filepath2[200];
		cout << "�����б�\n1. �鿴�豸�Ĵ洢����״̬\n";
		cout << "2. ���Ʊ����ļ����豸ָ��Ŀ¼\n3. �����豸�ļ�������ָ��Ŀ¼\n4. ��װ Android �����豸�����Ѳ��� Anbox��\n5. ж�� Android Ӧ�ó���\n";
		cout << "6. �����豸���\n7. ���ش洢ϵͳ�ɶ�д\n8. �����豸��ˢ��ģʽ\n9. ǿ�ƹػ�\n10. ǿ����������\n";
		cout << "11. ������������ԭ��������\n12. �����豸�ն�" << endl << "--> ";
		cin >> choice;
		cout << endl;
		if (choice == 1) {
			adb_shell("df -H");
			cout << endl;
		}	//ѡ��1
		else if (choice == 2) {
			cout << "�����ļ�·����";
			cin >> filepath1;
			cout << "�豸Ŀ��Ŀ¼·��ѡ��\n1. ��Ŀ¼\n2. Documents\n3. Downloads\n4. Music\n5. Pictures\n6. Videos\n--> ";
			cin >> choice;
			if (choice == 1)
				file_push(filepath1, "/home/phablet");
			else if (choice == 2)
				file_push(filepath1, "/home/phablet/Documents");
			else if (choice == 3)
				file_push(filepath1, "/home/phablet/Downloads");
			else if (choice == 4)
				file_push(filepath1, "home/phablet/Music");
			else if (choice == 5)
				file_push(filepath1, "/home/phablet/Pictures");
			else if (choice == 6)
				file_push(filepath1, "/home/phablet/Videos");
			cout << endl;
		}	//ѡ��2
		else if (choice == 3) {
			cout << "�豸�ļ�·����";
			cin >> filepath2;
			cout << "����Ŀ��Ŀ¼·����";
			cin >> filepath1;
			file_pull(filepath2, filepath1);
			cout << endl;
		}	//ѡ��3
		else if (choice == 4) {
			char save_path[300] = "/home/phablet/Downloads";
			char *apk_name;
			int count = 0;
			int flag;
			cout << "���ذ�׿�ļ�·����";
			cin >> filepath1;
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
				}	//�ҵ� .apk ����
			}	//�õ� apk �ļ���
			apk_name = new char [count];
			apk_name[count - 1] = '\0';
			for (int i = flag + 1, k = 0, calc = 0; calc < count; calc++, i++, k++) {
				apk_name[k] = filepath1[i];
			}	//�õ� apk �ļ���
			cout << "APK �ļ�����" << apk_name << endl;
			strcat(save_path, "/");
			strcat(save_path, apk_name);
			apk_inst(save_path);
			cout << endl;
		}	//ѡ��4
		else if (choice == 5) {
			char package[200];
			char uninst[500] = "adb uninstall ";
			cout << "APK ���б����£�" << endl;
			adb_shell("adb shell pm list packages");
			cout << endl << "�������Ӧ������ж�� Android Ӧ�ó���";
			cin >> package;
			adb_shell(strcat(uninst, package));
			cout << endl;
		}	//ѡ��5
		else if (choice == 6) {
			cout << "�����뱾��Ŀ��Ŀ¼·����";
			cin >> filepath1;
			file_pull("/home/phablet/Pictures", filepath1);
			cout << endl;
		}
		else if (choice == 7) {
			cout << "�������Ա�������û�Ȩ�ޣ���������ɲ���\n";
			adb_shell("sudo mount -o remount,rw /");
		}
		else if (choice == 8) {
			system("adb reboot bootloader");
		}
		else if (choice == 9) {
			system("adb shell reboot -p");
		}
		else if (choice == 10) {
			system("adb reboot");
		}
		else if (choice == 11) {
			system("adb reboot bootloader");
			system("fastboot format cache");
			system("fastboot format userdata");
			system("fastboot reboot");
		}
		else if (choice == 12) {
			system("adb shell");
		}
	}	//�����б�ѭ��
}