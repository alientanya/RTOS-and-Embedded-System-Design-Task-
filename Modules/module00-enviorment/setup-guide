# Module 00 - Setup Guide

## Install WSL

Open PowerShell as Administrator:

```powershell
wsl --install
```

Restart the PC if required.

Verify installation:

```powershell
wsl --status
```

---

## Enter Linux

```powershell
wsl
```

---

## Install Development Tools

```bash
sudo apt update
sudo apt install build-essential git cmake gdb
```

Verify:

```bash
gcc --version
git --version
cmake --version
gdb --version
```

---

## Create Workspace

```bash
cd ~
mkdir workspace
cd workspace
```

Verify location:

```bash
pwd
```

Expected:

```text
/home/<username>/workspace
```

---

## Create First Program

```bash
nano main.c
```

Example:

```c
#include <stdio.h>

int main(void)
{
    printf("Hello\n");
    return 0;
}
```

Save:

```text
Ctrl + O
Enter
Ctrl + X
```

Compile:

```bash
gcc main.c -o hello
```

Run:

```bash
./hello
```

---

## Configure Git

```bash
git config --global user.name "YourGitHubUsername"
git config --global user.email "your_email@example.com"
```

Verify:

```bash
git config --global --list
```

---

## Create SSH Key

```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```

Display public key:

```bash
cat ~/.ssh/id_ed25519.pub
```

Add the key to GitHub:

Settings → SSH and GPG Keys → New SSH Key

Test:

```bash
ssh -T git@github.com
```

Expected:

```text
Hi <GitHubUsername>! You've successfully authenticated...
```

---

## Clone Repository

```bash
cd ~/workspace
git clone git@github.com:<username>/<repository>.git
```

Enter repository:

```bash
cd <repository>
```

---

## First Commit

Check status:

```bash
git status
```

Add files:

```bash
git add .
```

Create commit:

```bash
git commit -m "Initial commit"
```

Push:

```bash
git push origin main
```

---

## Completion Checklist

* [ ] WSL installed
* [ ] GCC installed
* [ ] Git installed
* [ ] CMake installed
* [ ] GDB installed
* [ ] First C program compiled
* [ ] Git configured
* [ ] SSH configured
* [ ] Repository cloned
* [ ] First commit pushed

