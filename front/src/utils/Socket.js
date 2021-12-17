/** Import */
const net = require('net')
const { ipcMain } = require('electron')

class Socket {
  constructor(host, port, win) {
    this.host = host
    this.port = port
    this.win = win
    this.client = null

    this.connectToSocket()
  }

  connectToSocket() {
    this.client = net.connect({ host: this.host, port: this.port })
  }

  listenMsg() {
    this.listenBrowserMsg()
    this.listenSocketMsg()
  }

  listenBrowserMsg() {
    ipcMain.on('message-from-browser', (event, arg) => {
      this.sendMsgToSocket(arg)
    })
  }

  listenSocketMsg() {
    this.client.on('data', (data) => {
      this.sendMsgToBrowser(data)
    })
  }

  sendMsgToSocket(msg) {
    this.client.write(msg)
  }

  sendMsgToBrowser(data) {
    this.win.webContents.send('message-from-socket', data.toString())
  }
}

export default Socket
