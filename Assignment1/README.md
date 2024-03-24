# GAME PROGRAMMING

## Assignment 1:

* Docs: https://www.pygame.org/docs/

### How to run

1. First install conda: https://docs.conda.io/projects/conda/en/latest/user-guide/install/download.html
2. Make sure you can use the ```conda``` cmd by typing:
```bash
conda --version
```
3. Pull this project on github:
```bash
cd <Your/folder/path>
git init
git remote add origin https://github.com/dangnguyenblackie/GameProgamming
git fetch
git checkout master
```
4. Init conda
```bash
conda init bash
source ~/.bashrc
```
* Note: If you use another SHELL, you can change the name based on your SHELL. For me, I am using zsh SHELL then i typed:
```bash
conda init zsh
source ~/.zshrc
```
Then you should reset your TERMINAL.

5. Set up environment:
```bash
conda create --name <YOUR_ENV_NAME> --file requirements.txt
```
6. Then when you need to run the project:
```bash
# Activate env
conda activate <YOUR_ENV_NAME>

# RUN
python src/main.py
```

# END   
