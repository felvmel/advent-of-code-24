use regex::Regex;
use std::env;
use std::fs;
use std::path::Path;

fn do_mul(_mul: &str) -> i64 {
    let regex = Regex::new(r"(\d{1,3})").unwrap();
    let numbers: Vec<i64> = regex
        .find_iter(_mul)
        .filter_map(|digits| digits.as_str().parse().ok())
        .collect();
    numbers[0] * numbers[1]
}

fn do_part(part: &str) -> i64 {
    let regex = Regex::new(r"mul\(\d{1,3},\d{1,3}\)").unwrap();
    let result = regex.captures_iter(part);

    let mut sum: i64 = 0;
    for cap in result {
        sum += do_mul(cap.get(0).map_or("", |m| m.as_str()));
    }

    sum
}

fn main() {
    let path = env::current_dir().unwrap();
    println!("{}", path.display());

    let mut parent_path: String = Path::new(&path)
        .parent()
        .and_then(Path::to_str)
        .unwrap()
        .to_string();

    let input_file: &str = "\\input";
    parent_path.push_str(input_file);
    println!("{}", parent_path);

    let contents = fs::read_to_string(parent_path).expect("Should have been able to read the file");

    // split am dont
    let parts: Vec<&str> = contents.split("don\'t()").collect();
    let mut sum = do_part(parts[0]);
    for index in 1..(parts.len() - 1) {
        sum += do_part(parts[index].splitn(2, "do()").nth(1).unwrap_or(""));
    }

    println!("SUM: {}", sum);
}
