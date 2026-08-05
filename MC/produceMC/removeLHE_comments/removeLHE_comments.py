# Python script to remove comments from LHE files
import os
import sys

def remove_comments_from_lhe(lhe_filename):
    # Step 1: Define the source and target directories
    source_dir = "/eos/cms/store/group/phys_heavyions/clemahie/LHE_files"
    target_dir = "/eos/cms/store/group/phys_heavyions/clemahie/LHE_files_noComments"
    #source_dir = "/eos/user/c/clemahie"
    #target_dir = "/eos/user/c/clemahie"
    
    # Ensure the target directory exists
    os.makedirs(target_dir, exist_ok=True)
    
    # Full path to the source LHE file
    source_file = os.path.join(source_dir, lhe_filename)
    
    # Create the target filename by replacing 'pythia_' with 'new_pythia_'
    target_filename = lhe_filename.replace("pythia_", "new_pythia_")
    
    # Full path to the target LHE file
    target_file = os.path.join(target_dir, target_filename)
    
    # Step 2: Copy the file while removing comments before line 2200
    with open(source_file, 'r') as src_file, open(target_file, 'w') as dest_file:
        for line_num, line in enumerate(src_file, start=1):
            if line_num >= 2200 or not line.startswith('#'):
                dest_file.write(line)
    
    print(f"Processed file saved to: {target_file}")

if __name__ == "__main__":
    # Ensure the script is called with one argument
    if len(sys.argv) != 2:
        print("Usage: python3 removeLHE_comments.py pythia_${index}.lhe")
        sys.exit(1)
    
    # Get the LHE file name from the command-line argument
    lhe_filename = sys.argv[1]
    
    # Call the function with the provided filename
    remove_comments_from_lhe(lhe_filename)

