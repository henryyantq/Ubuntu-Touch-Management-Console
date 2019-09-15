# Ubuntu-Touch-Management-Console
Connect your Ubuntu Touch device to your computer and manage it with UT Management Console.

- File transfer
- Export & import photo album(s)
- Import videos & music (files or folder)
- External data backup
- Terminal operations
- Anbox (Android-in-a-box) related operations
- Libertine Container Management
- Bootloader (Fastboot mode) related operations
- More features will be added in the future
- There may be some bugs at present, please understand. I'm still a rookie LOL! Thanks for your support and suggestions (if you have)!!!
- LICENSE HAS BEEN ADDED! You can find it on another branch if you want ^_^

Note: Whether Anbox related operations can be done depends on whether the Android emulator on your Ubuntu Touch device is working properly. If the operations fail, in most cases you might need to check if the Anbox on your UT device really works properly or not.

This programme is only for Windows! I'll rewrite the terminal pipe operation to add support for Mac soon!

About Wget: So far, Wget for UTMC must be placed under the folder where ADB setups are. If you place it under System32 directly, UTMC might not be able to detect and launch related options correctly in some cases.

About VC_Redist: So far, a few PCs have (32-bit's are more likely to) shown the issue 'missing api-ms-win-crt-runtimel1-1-0.dll' when initializing UTMC. The most efficient solution so far is installing VC_Redist as a gadget (or something like that).
Attention: VC_Redist is not an essential widget for all PCs. Actually, the installation is only required after the issue above certainly shows up.

注意：不建议在大多数公共机房的 Windows 计算机上使用 UTMC，因为许多机器搭载的是经过定制的 Windows 系统，USB 端口适配性较低，可能出现 ADB 无法读取到您的设备的情况。对此我们并无解决方案，该问题也并非由 UTMC 及其插件的不完整性或不稳定性导致。建议您使用配备正版 Windows 操作系统（Windows 7 的较后期稳定版本、Windows 8.1 稳定版本与 Windows 10 稳定版本）的个人电脑操作 UTMC！

My emails:
yantq0927@gmail.com | henry0927@outlook.com

Find me on https://forums.ubports.com/ (UBports Forum): @Evergardener

通常，中文版更新进度较超前。请华人 UT 机友们尽量复制中文版的源码！
Sometimes, the update progress of Chinese version is more ahead of schedule. Sorry for the inconvenience!

感谢 Frank Pan，Ubuntu Touch 管理终端即将支持德语！
Dank Frank Pan wird das Ubuntu Touch Management Console bald Deutsch unterstützen!
