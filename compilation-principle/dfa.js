const fs = require('fs')

// 给定 DFA 图对应的信息，输出 DFA 可视化图形
const parseδ = ({S, Σ, s0, F, δ}) => {
  let result = ''

  result += 'strict digraph {\n'
  result += '\tstart [label="start", shape="diamond"]\n'
  // 结束节点样式定义
  F.forEach((state) => {
    result += `\t"${state}" [label="${state}", shape="doublecircle"]\n`
  })
  // 生成节点和连线
  S.forEach((state) => {
    Σ.forEach((input) => {
      if (δ[state][input] !== null && δ[state][input] !== '') {
        result += `\t"${state}" -> "${δ[state][input]}" [label = ${input}]\n`
      }
    })
  })
  result += `\tstart -> ${s0}\n`
  result += '}\n'

  return result
}

// 生成 dot 文件
exports.dfa = ({S, Σ, s0, F, δ, fileName = 'dfa'}) => {
  fs.writeFile(`./${fileName}.dot`, parseδ({S, Σ, s0, F, δ}), (error) => {
    if (error) {
      console.log(`error: ${error.message}`)
      return
    }
  })
}

// 给定 DFA 表格和输入字符串，判断该串是否被 DFA 接收
exports.judgeDFA = (δ, inputString, s0, F) => {
  let index = 0
  let nextState = s0
  while (index < inputString.length) {
    if (!δ[nextState]) return false
    nextState = δ[nextState][inputString[index]]
    index++
  }
  return F.indexOf(nextState) !== -1
}
