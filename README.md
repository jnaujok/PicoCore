# PicoCore
<div align="center"><img src="https://img.shields.io/badge/Raspberry%20Pi-A22846?style=for-the-badge&logo=Raspberry%20Pi&logoColor=white" /> <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" /><img src="https://img.shields.io/badge/Apache--2.0-green?style=for-the-badge" /></div><br/>
<div align="center"><a href="https://github.com/RichardLitt/standard-readme"><img src="https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square" /></a>
</div><br/>
<div align="center"><img src="https://img.shields.io/badge/sponsor-30363D?style=for-the-badge&logo=GitHub-Sponsors&logoColor=#white" /></div>

## Description

PicoCore is a C++ library designed to implement an inheritable framework allowing the user to rapidly develop prototype embedded software in a simple paradigm that hides most of the circuit-level difficulty of working with the various elements. 

To do this, it uses the dual-core nature of the R2040/2035 to create a "real-time" core and an "event-driven" core that can be used together to implement a system that either performs real-time operations, or responds to events, or, more often, a combination of the two.

Hardware interfaces are developed as "drivers" that abstract away most of the difficulties in working with the hardware, and shield the user from more common errors and issues. This includes implementations of SPI and I2C built to use the DMA support of the Pico to send and receive commands and data without user interaction. Interrupts can also be handled as either real-time drivers or pushed as events on the queue, when the data is not time-critical. 

Vendors could use this framework to develop drivers for their hardware, making it quick and easy for users to implement their hardware without having to learn a difficult handshake or protocol.

Additionally, some abstract drivers are provided to make the use of certain classes of hardware easier, for example, a generic SPI Video driver for running displays. A given physical display can inherit from this abstract driver allowing software to be written that will simply work, even if a new display is used instead. 

The target audience for this project are hobbyists who are just starting out in the land of embedded controllers like the Pico, but who still want a powerful enough system to be used for real projects with very little overage.

The main advantage of this system is that it is encoded entirely in C++, which means that it does not sacrifice performance for ease of use, like Micro Python does. 

## Table of Contents

- [Background](#background)
- [Installation](#installation)
- [Usage](#usage)
	- [Generator](#generator)
- [Features](#features)
- [Badge](#badge)
- [Related Efforts](#related-efforts)
- [Maintainers](#maintainers)
- [Contributing](#contributing)
- [License](#license)

## Background
I spent a lot of time working with embedded processors as a teenager forty years ago, and I was somewhat shocked to find that not a lot has changed in how embedded work is done today. When I first started using the Raspberry Pi Pico, it felt like I had gone back about forty years in software development style and quality of the tools. This was barely a step up from the Avocet 8051 Assembler that I used in 1986. 

Sure, there is a full Pico library of C calls that can be used that cover a large portion of the processor, but here was a CPU with orders of magnitude more power, and I was still slogging through the steps to set up a GPIO port for input or output, and 90% of the questions on Reddit are basic questions of how to use the CPU to turn on a single LED. 

Now admittedly a large part of that is dealing with the electrical engineering portions of the problem, but just as large is a fundamental misunderstanding of how a CPU works at a core level. 

These things don't have an operating system. There's no such thing as a file, or a stdout console. 

Which is a sad thing, because in this day and age, a lot of that should be a lot easier to do.

I started working on a CubeSat project, and almost immediately ran into massive short-comings with the basic way the CPU was set up. It has a massive amount of capability, but almost no one uses it, because it's hard to wrap your head around concepts like DMA, SPI, and I2C if you haven't done a lot of embedded coding before. 

So, that's why I started building this library, and I hope it can become the basis for a sea-change in the industry, where anyone can create some of these powerful IoT devices quickly and easily. 

## Installation
Installation of the kit is simple. Download the library into your Pico project, and add it to your make file like this...

(Details to be added)

## Usage
Examples and instructions demonstrating how to use the project, including code snippets, commands, or screenshots.

## Features
A list highlighting the main functionalities and capabilities of the project.

## Badge


## Related Efforts

Information about the languages, frameworks, libraries, and tools used in the project's development.

## Maintainers

The primary contributor to this project is Jeffrey Naujok.

## Contributing
Individuals who wish to contribute to the project should contact the maintainer before beginning a large effort. 

Drivers for hardware devices will be reviewed and accepted in the accompanying PicoCore-Drivers project. (TBD) 

Bug reports should be added to the issue tracker in GitHub. Feature requests should also be added there.

Pull requests will be rejected unless you have previously contacted the maintainer about adding code. 

(More details needed)

## License

[Apache GPL2.0](LICENSE) © 2025, Jeffrey Naujok
