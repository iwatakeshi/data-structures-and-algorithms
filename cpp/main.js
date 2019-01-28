const {
  performance
} = require('perf_hooks');

function time(lambda) {
  let start = performance.now();
  lambda();
  let stop = performance.now();

  return (stop - start)
}

function test(i, lambda) {
  for (let j = 1; j < i * 10000; j++) {
    lambda(j)
  }
}

function print_test(name, index) {
  console.log(`${name} - ${index * 10000} elements`)
}

function print_time(time) {
  console.log(`time: ${time}`)
  console.log()
}

function main() {
  
  for (let i = 1; i <= 10; i++) {
    let a = []
    let duration = 0.0;

    print_test("push", i)
    duration = time(() => {
      test(i, (j) => {
        a.push(j)
      })
    })

    print_time(duration)
  }
}

main();