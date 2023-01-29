let δ
let stateIndex
let getNextState = () => `s${++stateIndex}`
let getPrevState = () => `s${stateIndex - 1}`

// 为 δ 中的可到达集合添加一个值
const setReachableArray = (state, letter, value) => {
  δ[state][letter].indexOf(value) === -1 && δ[state][letter].push(value)
}

// 给定正则字符串，输出 NFA 表格
const parseRegular = (string, Σ, prevState, prevLetter, isCircle, createItem) => {
  let subStartState
  let resultStartState
  let ps = prevState
  let pl = prevLetter
  let subLeft = string.indexOf('(')
  let subRight = string.lastIndexOf(')')

  // 设置基于当前字符串的开始状态
  const setResultStartState = (state) => !resultStartState && (resultStartState = state)
  // 状态转移处理函数
  const move = (start, input, end) => {
    setResultStartState(end)
    setReachableArray(start, input, end)
    ps = end
    pl = input
  }

  {
    // 或的情况优先考虑，找到最外层的“或”符号
    let brackets = 0
    let orIndexes = [-1]
    for (let i = 0; i < string.length; i++) {
      if (string[i] === '(') ++brackets
      if (string[i] === ')') --brackets
      if (string[i] === '|' && brackets === 0) orIndexes.push(i)
    }
    orIndexes.push(string.length)
    // 如果在最外层有“或”符号，递归处理
    if (orIndexes.length > 2) {
      for (let i = 0; i < orIndexes.length - 1; i++) {
        const subString = string.slice(orIndexes[i] + 1, orIndexes[i + 1])
        subStartState = parseRegular(subString, Σ, ps, pl, true, createItem)
        setResultStartState(subStartState)
      }
      return resultStartState
    }
  }

  for (let i = 0; i < string.length; i++) {
    !δ[ps] && (δ[ps] = createItem())
    if (i === subLeft) {
      // 括号享有最高优先级，递归计算
      const subString = string.slice(subLeft + 1, subRight)
      subStartState = parseRegular(subString, Σ, ps, pl, false, createItem)
      setResultStartState(subStartState)
      // 跳过当前括号内容，已经在子递归中处理完毕
      i = subRight
    } else if (Σ.indexOf(string[i]) !== -1) {
      // 当前字符是字母表内的字符
      if (string.length === 1) {
        move(ps, string[i], ps)
      } else if (i !== string.length - 1 || !isCircle) {
        // 外层不是“或”且当前字符不是末尾字符
        if (string[i + 1] === '*') {
          pl = string[i]
          continue
        } else move(ps, string[i], getNextState())
      } else move(ps, string[i], getPrevState())
    } else if (string[i] === '*') {
      move(ps, pl, ps)
    }
  }

  !δ[`s${stateIndex}`] && (δ[`s${stateIndex}`] = createItem())
  return resultStartState
}

// 初始化处理工作
exports.nfa = (string, Σ) => {
  δ = {}
  stateIndex = 0
  parseRegular(string, Σ, 's0', undefined, false, () => {
    let item = {}
    Σ.forEach((letter) => (item[letter] = []))
    return item
  })
  return δ
}
