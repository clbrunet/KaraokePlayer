import os
import subprocess
import sys

def main():
    if len(sys.argv) > 2:
        print("usage:\n\tpython3 release_build.py [release_build_dir]")
        return
    release_build_dir = 'release_build'
    if len(sys.argv) > 1:
        release_build_dir = sys.argv[1]
    os.makedirs(release_build_dir, exist_ok=True)
    subprocess.check_call('cmake -DCMAKE_BUILD_TYPE=Release -B ' + release_build_dir, shell=True)
    subprocess.check_call('cmake --build .', shell=True, cwd=release_build_dir)
    subprocess.check_call('cp -r assets ' + release_build_dir, shell=True)
    subprocess.check_call('cp -r shaders ' + release_build_dir, shell=True)

if __name__ == '__main__':
    main()
