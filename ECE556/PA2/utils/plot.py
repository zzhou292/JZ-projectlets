import matplotlib.pyplot as plt
import matplotlib.patches as patches
import sys

def read_block_data(file_path):
    blocks = []
    with open(file_path, 'r') as f:
        lines = f.readlines()
        
        for line in lines:
            parts = line.strip().split()
            if len(parts) == 5:  # Expected format: name, x1, y1, x2, y2
                name = parts[0]
                x1, y1, x2, y2 = map(float, parts[1:])
                blocks.append((name, x1, y1, x2, y2))
    return blocks

def visualize_blocks(blocks):
    fig, ax = plt.subplots()
    min_x, min_y, max_x, max_y = float('inf'), float('inf'), float('-inf'), float('-inf')
    for block in blocks:
        name, x1, y1, x2, y2 = block
        min_x, min_y = min(min_x, x1), min(min_y, y1)
        max_x, max_y = max(max_x, x2), max(max_y, y2)
        width, height = x2 - x1, y2 - y1
        print(f"Adding block {name} with width {width} and height {height}")  # Diagnostic print
        ax.add_patch(patches.Rectangle((x1, y1), width, height, edgecolor='r', facecolor='none'))
        ax.text((x1+x2)/2, (y1+y2)/2, name, ha='center', va='center')
    ax.set_aspect('equal', 'box')
    ax.set_xlim([min_x, max_x])
    ax.set_ylim([min_y, max_y])
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script_name.py <output_file_path>")
        sys.exit(1)
    
    # Path to the output file from the first command line argument
    output_file_path = sys.argv[1]
    
    # Read block data from the file
    blocks = read_block_data(output_file_path)
    print(len(blocks))

    # Call the function with the path to your output file
    visualize_blocks(blocks)
