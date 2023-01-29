const {dfa, judgeDFA} = require('./dfa')
const nfa = require('./nfa').nfa
const n2d = require('./n2d').n2d

// nfa 测试
const n1 = nfa('1(0|1)*101', ['0', '1'])
const n2 = nfa('a((a|b)*|ab*a)*b', ['a', 'b'])

console.log(n1)
console.log(n2)

// nfa 转换测试
const d1 = n2d(n1, ['0', '1'], 's0')
const d2 = n2d(n2, ['a', 'b'], 's0')

console.log(d1)
console.log(d2)

const createF = (nδ, dδ) => {
  const states = Object.keys(nδ)
  const end = states[states.length - 1]
  return Object.keys(dδ).filter((state) => state.indexOf(end) !== -1)
}

// dfa 测试
console.log(judgeDFA(d1, '10101', 's0', createF(n1, d1)))
console.log(judgeDFA(d1, '10201', 's0', createF(n1, d1)))
console.log(judgeDFA(d1, '10100', 's0', createF(n1, d1)))
console.log(judgeDFA(d2, 'ababab', 's0', createF(n2, d2)))
console.log(judgeDFA(d2, 'abacab', 's0', createF(n2, d2)))
console.log(judgeDFA(d2, 'ababaa', 's0', createF(n2, d2)))

dfa({
  S: Object.keys(d1),
  Σ: ['0', '1'],
  s0: 's0',
  F: createF(n1, d1),
  δ: d1,
  fileName: 'd1',
})

dfa({
  S: Object.keys(d2),
  Σ: ['a', 'b'],
  s0: 's0',
  F: createF(n2, d2),
  δ: d2,
  fileName: 'd2',
})
