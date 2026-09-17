#include <stdio.h>
#include <unistd.h> // TODO: fix for platform-independent import

#define GRID_COLS 20
#define GRID_ROWS 20
#define GRID_CELLS (GRID_COLS * GRID_ROWS)
#define ALIVE '*'
#define DEAD '.'

/* Translates the specified x, y grid point into the index in the linear array.
 * This function also implements wrapping, so both positive and negative coordinates
 * that are out of the grid will wrap around. */
int cell_to_index(int x, int y) {
    if (x < 0) {
        x = (-x) % GRID_COLS;
        x = GRID_COLS - x; // it's negative: start from the end
    }
    if (y < 0) {
        y = (-y) % GRID_ROWS;
        y = GRID_ROWS - y; // it's negative: start from the end
    }
    if (x >= GRID_COLS) x = x % GRID_COLS;
    if (x >= GRID_ROWS) x = x % GRID_ROWS;

    return y * GRID_COLS + x;
}

/* Returns the state of the cell at [x, y]. */
char get_cell(char *grid, int x, int y) {
    return grid[cell_to_index(x, y)];
}

/* Sets the specified cell at [x, y] to the specified state [ALIVE or DEAD]. */
void set_cell(char *grid, int x, int y, char state) {
    grid[cell_to_index(x, y)] = state;
}

/* Shows the grid on the screen,
 * clearing the terminal using the required VT100 escape sequence. */
void print_grid(char *grid) {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            printf("%c", get_cell(grid, x, y));
        }
        printf("\n"); // return at each "row"
    }
}

/* Sets all the grid cells to the specified state. */
void set_grid(char *grid, char state) {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            set_cell(grid, x, y, state);
        }
    }
}

/* Returns the number of living neighbor cells of [x, y] */
int count_living_neighbors(char *grid, int x, int y) {
    int alive = 0;

    for (int y_offset = -1; y_offset <= 1; y_offset++) {
        for (int x_offset = -1; x_offset <= 1; x_offset++) {
            if (x_offset == 0 && y_offset == 0) continue;
            if (get_cell(grid, x+x_offset, y+y_offset) == ALIVE) alive++;
        }
    }

    return alive;
}

/* Computes the new state of the game according to its rules. */
void compute_new_state(char *old, char *new) {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            int n_alive = count_living_neighbors(old, x, y);
            int new_state = DEAD;
            if (get_cell(old, x, y) == ALIVE) {
                if (n_alive == 2 || n_alive == 3) new_state = ALIVE;
            } else {
                if (n_alive == 3) new_state = ALIVE;
            }

            set_cell(new, x, y, new_state);
        }
    }
}

/* Prints the screen-clearing characters on the terminal. */
void clear_screen(void) {
    printf("\x1b[3J\x1b[H\x1b[2J"); // TODO: this does not work on Windows
}

int main(void) {
    clear_screen();

    char old_grid[GRID_CELLS];
    char new_grid[GRID_CELLS];

    set_grid(old_grid, DEAD);
    // for infinite "plus" sign
    // set_cell(old_grid, 10, 10, ALIVE);
    // set_cell(old_grid, 10, 11, ALIVE);
    // set_cell(old_grid, 10, 12, ALIVE);
    // for classic "glider"
    set_cell(old_grid, 10, 10, ALIVE);
    set_cell(old_grid, 9, 10, ALIVE);
    set_cell(old_grid, 11, 10, ALIVE);
    set_cell(old_grid, 11, 9, ALIVE);
    set_cell(old_grid, 10, 8, ALIVE);

    while(1) {
        compute_new_state(old_grid, new_grid);
        print_grid(new_grid);
        usleep(1000000);
        compute_new_state(new_grid, old_grid);
        print_grid(old_grid);
        usleep(1000000);
    }

    // printf("%d", count_living_neighbors(old_grid, 10, 14));

    return 0;
}
