let δ
let T = [] // 未被跟踪的状态集合
let U = [] // 已被跟踪的状态集合

// 为状态集合取名，成为一个新的状态
const createStateName = (states) => {
  let name = ''
  states.forEach((state, index) => (name += state + (index === states.length - 1 ? '' : ',')))
  return name
}

const parseNFA = (nfa, Σ, createItem) => {
  // 沿着当前状态所能达到的状态
  const findStates = (states, letter) => {
    const set = new Set()
    states.forEach((state) => {
      nfa[state][letter].forEach((targetState) => {
        set.add(targetState)
      })
    })
    return Array.from(set)
  }

  // 有无未被追踪的状态集合
  while (T.length !== 0) {
    const states = T.shift()
    const originStateName = createStateName(states)
    !δ[originStateName] && (δ[originStateName] = createItem())
    // 对于当前状态集合，求特定输入下可以到达的目的状态集合
    Σ.forEach((letter) => {
      const newStates = findStates(states, letter)
      const targetStateName = createStateName(newStates)
      δ[originStateName][letter] = targetStateName
      states.forEach((state) => U.push(state))
      // 如果新集合内有没有被追踪的状态，则表示这是一个新状态
      newStates.forEach((state) => {
        if (U.findIndex((item) => item === state) === -1) T.push(newStates)
      })
    })
  }
}

// 给定 NFA 转换表，利用子集法生成 DFA
exports.n2d = (nfa, Σ, s0) => {
  δ = {}
  T = [[s0]]
  U = []
  parseNFA(nfa, Σ, () => {
    let item = {}
    Σ.forEach((letter) => (item[letter] = ''))
    return item
  })
  return δ
}
