from dash import Dash, html, dcc
import pandas as pd
import plotly.express as px
from dash.dependencies import Input, Output
import dash_bootstrap_components as dbc
from collections import deque
import time

app = Dash(__name__, external_stylesheets=[dbc.themes.SLATE])

#get method for tail of datagrame
def tail(filename, n=1):
    return deque(open(filename), n)

# Dataframe for gps data for now
# df = pd.read_csv('ui_data.txt',sep =',', names=['time', 'lat', 'long', 'stat', 'alt'], index_col=False)

app.layout = html.Div([
    dbc.Card(
        dbc.CardBody([
            dbc.Row([
                dbc.Col([
                    dcc.Graph(
                            id='3dline',
                    ),
                ], width=3),
                dbc.Col([
                    dcc.Graph(
                         id='gps',
                        # config={'staticPlot': True},
                    ), 
                ], width=4),
                dbc.Col([
                    dcc.Graph(
                        id='altie',
                    ),
                ], width=4),
            ], align='center'), 

            html.Br(),

            dbc.Row([
                dbc.Col([
                    dcc.Graph(
                        id='temp',
                    ),
                ], width=4),
                dbc.Col([
                    dcc.Graph(
                        id='humid',
                    ), 
                ], width=4),
            ], align='center'),    
        ]), color = 'dark',
    ),

    dcc.Interval(
            id='interval-component',
            interval=1*1000, # in milliseconds
            n_intervals=0,
    ),

],)

@app.callback(
    Output('3dline', 'figure'),
    Output('altie', 'figure'),
    # Output('temp', 'figure'),
    # Output('humid', 'figure'),
    Output('gps', 'figure'),
    Input('interval-component', 'n_intervals')
)
def update_alt_graph(n):
    # line = tail("ui_data.txt")[0]
    # line = line.split(",")
    # print(f"This is the split line: {line}")
    # line[-1] = line[-1][:-1]
    # print(f"This is the cleaned up line: {line}")
    # line_series = pd.DataFrame(line)
    # df = pd.concat([df, line_series], copy=False, ignore_index=True)
    # line_df = pd.read_table(tail,sep =',', names=['time', 'lat', 'long', 'stat', 'alt'], index_col=False)
    # print(f"DF:{df}")
    # print(f"line series: {line_series}\n\n-----------\n")
    # pd.concat([df, line_df], ignore_index=True)

    df = pd.read_csv('ui_data.txt',sep =',', names=['time', 'lat', 'long', 'stat', 'alt'], 
                     converters={'lat' : str, 'long' : str}, index_col=False)
    # The converters argument in read_csv changes the lat and long variables into strings so that leading 0's are preserved

    df.fillna(value=0, inplace=True)
    df.replace(to_replace =
               {'lat' : {'' : '0000.0000'}, 
                'long' : {'' : '00000.0000'}
                },
                inplace=True)
    
    print(f"df:\n{df}")
    raw_lat = df.lat.str
    lat_degrees = raw_lat[:2]
    lat_minutes = raw_lat[2:]
    #Convert the minutes into degrees by dividing by 60
    #Change type to float first
    lat_min_to_degrees = lat_minutes.astype("float") / 60
    # Add the converted minutes to the degrees
    converted_lats = lat_degrees.astype("float") + lat_min_to_degrees
    # converted_lats = converted_lats.astype("string")
    df["lat"] = converted_lats

    # Converting LONGS
    raw_long = df.long.str
    long_degrees = raw_long[:3]
    long_minutes = raw_long[3:]
    
    long_min_to_degrees = long_minutes.astype("float") / 60

    converted_longs = long_degrees.astype("float") + long_min_to_degrees
    # converted_longs = converted_longs.astype("string")
    df["long"] = (converted_longs * -1)

    print(f"df with adjusted coords:\n{df}")



    fig = px.line_3d(df, x="lat", y="long", z="alt" , markers = True, text = "time")    
    fig.update_layout(scene = dict(xaxis = dict(nticks=10, range=[-1000,8000]),
                                   yaxis = dict(nticks=10, range=[-1000,8000]),
                                   zaxis = dict(nticks=10, range=[0,300])),
                        uirevision='constant',
                        height=350, width=350,)

    
    altitude_graph = px.line(df, x="time", y="alt", title="Altitude test", markers=True, height=400, width=600, range_y=(10,130000))
    altitude_graph.update_layout(uirevision='constant')

    gpsgraph = px.line_mapbox(df, lat="lat", lon="long", zoom=2, height=400, width=470)
    gpsgraph.update_layout(mapbox_style="open-street-map", 
                           mapbox_zoom=2, 
                           mapbox_center_lat = 43, 
                           mapbox_center_lon = -75, 
                        #    mapbox_bounds_east=-69,
                        #    mapbox_bounds_north=46,
                        #    mapbox_bounds_south=38,
                        #    mapbox_bounds_west=-81,
                           margin={"r":0,"t":0,"l":0,"b":0},
                           uirevision='constant')
    
    # temperature_graph = px.line(df, x="time", y="temp", title="Temperature test", markers=True, height=250, width=500)
    # temperature_graph.update_layout(uirevision='constant')

    # humidity_graph = px.line(df, x="time", y="humid", title="Humidity test", markers=True, height=250, width=500)
    # humidity_graph.update_layout(uirevision='constant')

    return fig, altitude_graph, gpsgraph #temperature_graph, humidity_graph


if __name__ == '__main__':
    app.run_server(debug=True)
