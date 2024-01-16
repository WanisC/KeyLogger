#!usr/bin/env node

import chalk from "chalk"; // https://github.com/chalk/chalk
import inquirer from "inquirer";
import gradient from "gradient-string";
import chalkAnimation from "chalk-animation";
import figlet from "figlet";
import { createSpinner } from "nanospinner";
import readline from "readline";

// Global variables
const sleep_1s = (ms) => new Promise((resolve) => setTimeout(resolve, 1000));
const sleep_2s = (ms) => new Promise((resolve) => setTimeout(resolve, 2000));
const booting_load = (ms) =>
  new Promise((resolve) => setTimeout(resolve, 5000));

const booting_msg = [
  "You know it's illegal right.",
  "Here you are sneaky boy...",
  "Welcome dear, let's start our activities...",
  "WELCOME TO EXPERIMENT",
];
var x = Math.floor(Math.random() * 3);

var disp_msg = booting_msg[x];

const clearLastLine = () => {
  readline.moveCursor(process.stdout, 0, -1); // up one line
  readline.clearLine(process.stdout, 1); // from cursor to end
};
// Display banner
async function banner() {
  chalkAnimation.glitch(disp_msg);
  await booting_load();
  clearLastLine();

  console.log(
    figlet.textSync("Experiment", {
      font: "Standard",
      horizontalLayout: "default",
      verticalLayout: "default",
      width: 80,
      whitespaceBreak: true,
    })
  );

  console.log(
    chalk.yellow(
      "This command is for the purpose of the experiment. It is not intended for production use."
    )
  );
  console.log(
    chalk.yellow(
      "If you use it for production/malicious purposes, you are responsible for the consequences."
    )
  );
}

// Waiting for user input
async function waitForInput(cmd_input) {
  const message = cmd_input == null ? ">> " : `${cmd_input} >> `;
  const questions = [
    {
      type: "input",
      name: "command",
      message: message,
    },
  ];
  const answers = await inquirer.prompt(questions);
  handleInput(answers.command);
}

// Display help
async function caseHelp() {
  console.log("Usage \n");
  console.log("\tThis command will give you access to simple actions.");
  console.log("\tA keylogger and a scanner of local IP adress.");
  console.log("Actions \n");
  console.log(
    "\tkeylogger: will run and capture all key presses on the computer and store it into a file."
  );
  console.log("\t\tParameters \n");
  console.log("\t\t\tlisten: start a session.");
  console.log("\t\t\tstop: kill the session.");
  console.log("\t\t\tshow: print the file. \n");
  console.log(
    "\tscan: will run a scanner and catch all devices connected into the same network, when this command will be executed just wait until the scanner is done."
  );
}

// Activate keylogger
async function caseKeylogger() {
  console.log(chalk.red("Not implemented yet."));
}

// Scan local network
async function caseScan() {
  console.log(chalk.red("Not implemented yet."));
}

// Handle user input
async function handleInput(cmd_input) {
  // Handle commands
  switch (cmd_input) {
    case "help":
      console.log("Generating 'help' documentation");
      await caseHelp();
      cmd_input = await waitForInput(null);
    case "exit":
      console.log("Nooooooo, why you're leaving me again");
      break;
    case "keylogger":
      console.log("Let's start a listener");
      cmd_input = await waitForInput(cmd_input);
    case "scan":
      console.log("Scanner of your local network");
      cmd_input = await waitForInput(cmd_input);
    default:
      console.log(chalk.red("Command not found."));
      console.log("Type 'help' for help.");
      cmd_input = await waitForInput(null);
  }
}

await banner();
await waitForInput();
