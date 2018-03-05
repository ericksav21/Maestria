library("shiny")
library("e1071")
library("entropy")

ui <- fluidPage(
  
  # App title ----
  titlePanel("Simulación de Kurtosis y Neguentropía."),
  
  # Sidebar layout with input and output definitions ----
  sidebarLayout(
    
    # Sidebar panel for inputs ----
    sidebarPanel(
      selectInput("selectMode", label = h3("Modo:"), 
                  choices = list("Kurtosis" = 1, "Neguentropía" = 2), 
                  selected = 1),
      
      selectInput("selectDist", label = h3("Distribución:"), 
                  choices = list("Normal" = 1, "Uniforme" = 2, "Exponencial" = 3), 
                  selected = 1),
      
      sliderInput(inputId = "noVars",
                  label = "Número de variables:",
                  min = 10,
                  max = 100,
                  value = 30),
      
      sliderInput(inputId = "noObs",
                  label = "Número de observaciones:",
                  min = 10,
                  max = 100,
                  value = 30)
      
    ),
    
    # Main panel for displaying outputs ----
    mainPanel(
      
      # Output: Histogram ----
      plotOutput(outputId = "kurtPlot")
      
    )
  )
)

server <- function(input, output) {
  
  output$kurtPlot <- renderPlot({
    
    mode <- as.integer(input$selectMode)
    noVars <- as.integer(input$noVars)
    noObs <- as.integer(input$noObs)
    dist <- as.integer(input$selectDist)
    
    ind <- seq(1, noVars, by = 1)
    x <- rep(0, noObs)
    y <- rep(0, noVars)
    
    if(mode == 1) {
    
      for(n in 1:noVars) {
        if(dist == 1) {
          x <- x + rnorm(noObs)
        }
        else if(dist == 2) {
          x <- x + runif(noObs)
        }
        else {
          x <- x + rexp(noObs)
        }
        
        y[n] <- kurtosis(x)
      }
      
      plot(ind, y, xlab = "No. Variables", ylab = "Kurtosis", title("Evolución de la kurtosis"))
    }
    else {
      for(n in 1:noVars) {
        if(dist == 1) {
          x <- x + rnorm(noObs)
        }
        else if(dist == 2) {
          x <- x + runif(noObs)
        }
        else {
          x <- x + rexp(noObs)
        }
        
        aux <- rnorm(noObs, mean = mean(x), sd = sd(x))
        y[n] = entropy(aux) - entropy(x)
      }
      
      plot(ind, y, xlab = "No. Variables", ylab = "Neguentropía", title("Evolución de la neguentropía"))
    }
    
  })
  
}

shinyApp(ui = ui, server = server)