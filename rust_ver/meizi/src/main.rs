use std::fmt;

#[derive(Debug)]
struct Cell {
    row: i32,
    column: i32,
    value: i32
}

impl fmt::Display for Cell {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{:?}", self.value)
    }
}


struct Grid {
    grid: Vec<Vec<Cell>>
}

fn main() {
    let mut v = 1;
    let mut _grid = vec![];
    for r in 1..10 {
        let mut vector_row = vec![];
        for c in 1..10 {
            let cell = Cell{row: r, column: c, value: v};
            v = v + 1;
            vector_row.push(cell);
        }
        _grid.push(vector_row);
    }
    let g = Grid { grid: _grid };
    for v_r in g.grid {
        for c in v_r {
            println!("value - {}", c);
        }
    }

    // println!("{}", g);

    println!("Hello, world!");
}
