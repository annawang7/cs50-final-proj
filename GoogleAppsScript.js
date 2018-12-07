// Original gist: https://gist.github.com/willpatera/ee41ae374d3c9839c2d6 

// Upon HTTP GET request
function doGet(e) {
  return handleResponse(e);
}

// Stores script properties in a global variable
var SCRIPT_PROP = PropertiesService.getScriptProperties();

function handleResponse(e) {
  // Prevents concurrent editing of sheet
  var lock = LockService.getDocumentLock();
  
  // Waits 30 seconds before conceding
  lock.waitLock(30000)
  
  try {
    // Opens document based on script property key; see setup()
    var doc = SpreadsheetApp.openById(SCRIPT_PROP.getProperty("key"));
    
    // Gets first sheet
    var sheet = doc.getSheets()[0];
    
    // Sets variable equal to the number of rows passed in through the HTML form if received; else 1
    var headRow = e.parameter.header_row || 1;
    var headers = sheet.getRange(1, 1, 1, sheet.getLastColumn()).getValues()[0];
    
    // Increments row to get body of spreadsheet
    var nextRow = sheet.getLastRow() + 1;
    var row = [];
    
    // Loop through headers
    for (i in headers) {
      // Push timestamp to spreadsheet
      if (headers[i] == "timestamp") {
        row.push(new Date());
      } else {
        // Push form data: r, g, b
        Logger.log(e.parameter[headers[i]]);
        row.push(e.parameter[headers[i]]);
      }
    }
    
    // Loop through all cells
    sheet.getRange(nextRow, 1, 1, row.length).setValues([row]);
    
    // If success, return 'success' to text output
    return ContentService
    .createTextOutput(JSON.stringify({
      "result":"success",
      "row":nextRow
    }))
    .setMimeType(ContentService.MimeType.JSON);
  } catch(e) {
    
    // If failure, return 'error' to text output
    return ContentService.createTextOutput(JSON.stringify({
      "result":"error",
      "error":e
    }))
    .setMimeType(ContentService.MimeType.JSON);
  } finally {
    // Release lock
    lock.releaseLock();
  }
}
  
// Stores ID as a script property
function setup() {
  var doc = SpreadsheetApp.getActiveSpreadsheet();
  SCRIPT_PROP.setProperty("key", doc.getId());
}