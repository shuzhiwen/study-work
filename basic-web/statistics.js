var lecture = ''
var count = 8

window.onload = () => {
  fetchData('get_basicquestion', parseBasic)
  fetchData('get_practice', parsePractise)
  fetchData('get_comment', makeComments)
  fetchData('get_theory', parseTheory)
  $('submit').onclick = handleSearch
  $('more').onclick = handleMoreComments
  ;['toBasic', 'toTheory', 'toPractise', 'toComments'].forEach((id) => {
    $(id).onclick = () => setTimeout(() => window.scrollBy(0, -55), 0)
  })
  $$('#navbar .navbar-nav')[0].childNodes.forEach((element) => {
    element.onclick = (event) => {
      count = 8
      lecture = event.toElement.text.toLowerCase()
      ;['Basic', 'Theory', 'Practise', 'Comments'].forEach((id) => {
        $(id).innerHTML = id + ' @ ' + lecture.toLowerCase()
      })
    }
  })
}

function fetchData(tableName, callback, from = '2000-01-01 00:00:00', to = '2021-01-01 23:59:59') {
  let fetchUrl = 'http://cnxfs.com.cn:81/core.php'
  let fetchOption = {
    method: 'POST',
    headers: {
      Accept: 'application/json',
      'Content-Type': 'application/x-www-form-urlencoded',
    },
    body: `&todo=${tableName}&begintime=${from}&endtime=${to}&course=${lecture}&count=${count}`,
  }

  fetch(fetchUrl, fetchOption)
    .then((promise) => promise.json())
    .then((data) => {
      if (callback) {
        callback(data)
      }
    })
}

//////////////////////////////////////////////////////////////////////

function parseBasic(data) {
  if (data.length === 0) {
    makePie('basic', null, 'No Data')
    makePie('basic', null, 'No Data')
    makePie('basic', null, 'No Data')
    makePie('basic', null, 'No Data')
    return
  }

  let result = {
    lecturesatisfy: Array(7).fill(0),
    lecturetime: Array(7).fill(0),
    slidesatisfy: Array(7).fill(0),
    spendtime: Array(7).fill(0),
  }

  data.map(({course, id, lecturesatisfy, lecturetime, slidesatisfy, spendtime}) => {
    result.lecturesatisfy[lecturesatisfy - 1] += 1
    result.lecturetime[lecturetime - 1] += 1
    result.slidesatisfy[slidesatisfy - 1] += 1
    result.spendtime[spendtime - 1] += 1
  })

  makePie('basic', result.lecturesatisfy, 'Lecturesatisfy')
  makePie('basic', result.lecturetime, 'Lecturetime')
  makePie('basic', result.slidesatisfy, 'Slidesatisfy')
  makePie('basic', result.spendtime, 'Spendtime')
}

function parseTheory(data) {
  if (data.length === 0) {
    makePie('theory', null, 'No Data')
    makePie('theory', null, 'No Data')
    makePie('theory', null, 'No Data')
    makePie('theory', null, 'No Data')
    makePie('theory', null, 'No Data')
    return
  }

  let result = {
    concentrate: Array(7).fill(0),
    improvement: Array(7).fill(0),
    interest: Array(7).fill(0),
    quantity: Array(7).fill(0),
    question: Array(7).fill(0),
  }

  data.map(({course, id, concentrate, improvement, interest, quantity, question}) => {
    result.concentrate[concentrate - 1] += 1
    result.improvement[improvement - 1] += 1
    result.interest[interest - 1] += 1
    result.quantity[quantity - 1] += 1
    result.question[question - 1] += 1
  })

  makePie('theory', result.concentrate, 'Concentrate')
  makePie('theory', result.improvement, 'Improvement')
  makePie('theory', result.interest, 'Interest')
  makePie('theory', result.quantity, 'Quantity')
  makePie('theory', result.question, 'Question')
}

function parsePractise(data) {
  if (data.length === 0) {
    makePie('practise', null, 'No Data')
    makePie('practise', null, 'No Data')
    makePie('practise', null, 'No Data')
    return
  }

  let result = {
    applicability: Array(7).fill(0),
    difficulty: Array(7).fill(0),
    helplecture: Array(7).fill(0),
  }

  data.map(({course, id, applicability, difficulty, helplecture}) => {
    result.applicability[applicability - 1] += 1
    result.difficulty[difficulty - 1] += 1
    result.helplecture[helplecture - 1] += 1
  })

  makePie('practise', result.applicability, 'Applicability')
  makePie('practise', result.difficulty, 'Difficulty')
  makePie('practise', result.helplecture, 'Helplecture')
}

//////////////////////////////////////////////////////////////////////

async function handleSearch() {
  let from = $('from').value + ' 00:00:00'
  let to = $('to').value + ' 23:59:59'

  $('basic').innerHTML = null
  $('theory').innerHTML = null
  $('practise').innerHTML = null

  fetchData('get_basicquestion', parseBasic, from, to)
  fetchData('get_practice', parsePractise, from, to)
  fetchData('get_comment', makeComments, from, to)
  fetchData('get_theory', parseTheory, from, to)
}

function handleMoreComments() {
  count += 8
  fetchData('get_comment', makeComments)
}

//////////////////////////////////////////////////////////////////////

function makeComments(data) {
  $('comments').innerHTML = null
  data.map(({ctime, improvement, question}) => {
    let comment = document.createElement('div')
    comment.className = 'card text-center comment'

    let header = document.createElement('div')
    header.className = 'card-header'
    header.innerHTML = 'Comment'

    let footer = document.createElement('div')
    footer.className = 'card-footer text-muted'
    footer.innerHTML = ctime

    let body = document.createElement('div')
    body.className = 'card-body'

    let title = document.createElement('h5')
    title.className = 'card-title'
    title.innerHTML = question

    let text = document.createElement('p')
    text.className = 'card-text'
    text.innerHTML = improvement

    body.appendChild(title)
    body.appendChild(text)
    comment.appendChild(header)
    comment.appendChild(body)
    comment.appendChild(footer)
    $('comments').appendChild(comment)
  })
}

//////////////////////////////////////////////////////////////////////

function makePie(id, data, title) {
  let chart = document.createElement('div')
  let canvas = document.createElement('canvas')

  canvas.height = 1
  canvas.width = 1
  chart.className = 'chart'
  chart.appendChild(canvas)
  $(id).appendChild(chart)

  let ctx = canvas.getContext('2d')
  let myChart = new Chart(ctx, {
    type: 'pie',
    data: {
      labels: ['Score 1', 'Score 2', 'Score 3', 'Score 4', 'Score 5', 'Score 6', 'Score 7'],
      datasets: [
        {
          data: data,
          backgroundColor: [
            'rgba(255, 99, 132)',
            'rgba(54, 162, 235)',
            'rgba(255, 206, 86)',
            'rgba(75, 192, 192)',
            'rgba(153, 102, 255)',
            'rgba(255, 159, 64)',
            'rgba(180, 145, 115)',
          ],
        },
      ],
    },
    options: {
      title: {
        display: true,
        text: title,
        fontSize: 20,
      },
      animation: {
        animateScale: true,
      },
      scales: {
        yAxes: [
          {
            ticks: {
              callback: () => null,
            },
            gridLines: {
              display: null,
            },
          },
        ],
      },
    },
  })
}

function makeLineid(id, data, title) {
  let chart = document.createElement('div')
  let canvas = document.createElement('canvas')

  canvas.height = 1
  canvas.width = 1
  chart.className = 'chart'
  chart.appendChild(canvas)
  $(id).appendChild(chart)

  let ctx = canvas.getContext('2d')
  let myChart = new Chart(ctx, {
    type: 'line',
    data: {
      labels: ['Score 1', 'Score 2', 'Score 3', 'Score 4', 'Score 5', 'Score 6', 'Score 7'],
      datasets: [
        {
          label: 'rating',
          borderColor: '#FF9900',
          lineTension: 0,
          fill: false,
          data: data,
          pointBackgroundColor: '#CC0066',
        },
      ],
    },
    options: {
      title: {
        display: true,
        text: title,
        fontSize: 20,
      },
      scales: {
        yAxes: [
          {
            ticks: {
              max: 5,
              min: 0,
            },
          },
        ],
      },
    },
  })
}
