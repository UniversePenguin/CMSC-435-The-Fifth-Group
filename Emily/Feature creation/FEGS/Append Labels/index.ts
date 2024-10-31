// const validityCheck = /[^ACDEFGHIKLMNPQRSTVWY]/;

const full_file_unlabeled = await Bun.file("unlabeled_data.csv").text();
const formatted_data_unlabeled: string[][] = full_file_unlabeled.split("\r\n").map((x) => {
    const elements = x.split(",");
    return elements;
});

const full_file_labels = await Bun.file("labels.csv").text();
const formatted_data_labels: string[][] = full_file_labels.split("\r\n").map((x) => {
    const elements = x.split(",");
    return elements;
});

const lineate = (str: string): string => {
    return str.match(/\w{1,80}/g)?.join("\n") ?? "";
};

let output = "";

// console.log(formatted_data_labels);
console.log(formatted_data_unlabeled);

for (let i = 0; i < formatted_data_labels.length; i++) {
    const label = formatted_data_labels[i][1];
    formatted_data_unlabeled[i].unshift(label);
}

Bun.write("labeled_data.csv", formatted_data_unlabeled.map((x) => x.join(",")).join("\n"));
