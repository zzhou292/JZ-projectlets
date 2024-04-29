import matplotlib.pyplot as plt
import sys

def parse_pins_and_lines(pin_filename, line_filename):
    # Parsing pin locations
    pins = []
    with open(pin_filename, 'r') as file:
        for line in file:
            if line.startswith('PIN'):
                parts = line.split()
                pin_name = parts[1]
                coords = parts[2].strip('()').split(',')
                x, y = map(int, coords)
                pins.append((pin_name, x, y))

    # Parsing lines from previous logic
    h_lines, v_lines = [], []
    with open(line_filename, 'r') as file:
        for line in file:
            if line.startswith('H-line') or line.startswith('V-line'):
                parts = line.strip().split(' ')
                line_type = parts[0]  # "H-line" or "V-line"
                coords1 = parts[1].strip('()').split(',')
                coords2 = parts[2].strip('()').split(',')
                x1, y1 = int(coords1[0]), int(coords1[1])
                x2, y2 = int(coords2[0]), int(coords2[1])

                if line_type == 'H-line':
                    h_lines.append(((x1, x2), (y1, y2)))
                elif line_type == 'V-line':
                    v_lines.append(((x1, x2), (y1, y2)))

    return pins, h_lines, v_lines

def plot_lines_and_pins(pins, h_lines, v_lines):
    fig, ax = plt.subplots()
    # Plotting lines
    for x, y in h_lines:
        ax.plot(x, y, 'r-')  # red for horizontal lines
    for x, y in v_lines:
        ax.plot(x, y, 'b-')  # blue for vertical lines
    
    # Plotting pins
    for pin_name, x, y in pins:
        ax.plot(x, y, 'go')  # green 'o' for pins
        ax.text(x, y, pin_name, fontsize=9, ha='right')

    ax.set_title('Wire Routing Visualization with Pins')
    ax.set_xlabel('X Coordinate')
    ax.set_ylabel('Y Coordinate')
    plt.grid(True)
    plt.show()

def main():
    if len(sys.argv) != 3:
        print("Usage: python draw.py <pin_filename> <line_filename>")
        return

    pin_filename = sys.argv[1]  # First argument after the script name
    line_filename = sys.argv[2]  # Second argument after the script name
    pins, h_lines, v_lines = parse_pins_and_lines(pin_filename, line_filename)
    plot_lines_and_pins(pins, h_lines, v_lines)

if __name__ == '__main__':
    main()

