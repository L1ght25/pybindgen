import argparse
import json
import os


def main(out_directory, directory, file):
    data = {
        "directory": directory,
        "command": "clang++",
        "file": file
    }

    compilation_database_json = os.path.join(out_directory, "compile_commands.json")
    with open(compilation_database_json, "w") as afile:
        json.dump(data, afile)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--dir", help="directory in compile_commands.json")
    parser.add_argument("--gen_file", help="path to gen file")
    parser.add_argument("--out_dir", help="output dir")
    args = parser.parse_args()

    main(args.out_dir, args.dir, args.gen_file)
